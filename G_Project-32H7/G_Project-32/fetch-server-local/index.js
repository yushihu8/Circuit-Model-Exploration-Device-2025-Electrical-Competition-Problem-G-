#!/usr/bin/env node

import { Server } from '@modelcontextprotocol/sdk/server/index.js';
import { StdioServerTransport } from '@modelcontextprotocol/sdk/server/stdio.js';
import {
  CallToolRequestSchema,
  ErrorCode,
  ListToolsRequestSchema,
  McpError,
} from '@modelcontextprotocol/sdk/types.js';
import fetch from 'node-fetch';

const DEFAULT_LIMIT = process.env.DEFAULT_LIMIT ? parseInt(process.env.DEFAULT_LIMIT) : 5000;

class FetchServer {
  constructor() {
    this.server = new Server(
      {
        name: 'fetch-mcp-server',
        version: '1.0.0',
      },
      {
        capabilities: {
          tools: {},
        },
      }
    );

    this.setupToolHandlers();
    
    this.server.onerror = (error) => console.error('[MCP Error]', error);
    process.on('SIGINT', async () => {
      await this.server.close();
      process.exit(0);
    });
  }

  setupToolHandlers() {
    this.server.setRequestHandler(ListToolsRequestSchema, async () => ({
      tools: [
        {
          name: 'fetch_html',
          description: 'Fetch a website and return the content as HTML',
          inputSchema: {
            type: 'object',
            properties: {
              url: {
                type: 'string',
                description: 'URL of the website to fetch',
              },
              headers: {
                type: 'object',
                description: 'Custom headers to include in the request',
              },
              max_length: {
                type: 'number',
                description: 'Maximum length to fetch',
              },
              start_index: {
                type: 'number',
                description: 'Used together with max_length to retrieve contents piece by piece',
              },
            },
            required: ['url'],
          },
        },
        {
          name: 'fetch_json',
          description: 'Fetch a JSON file from a URL',
          inputSchema: {
            type: 'object',
            properties: {
              url: {
                type: 'string',
                description: 'URL of the JSON to fetch',
              },
              headers: {
                type: 'object',
                description: 'Custom headers to include in the request',
              },
              max_length: {
                type: 'number',
                description: 'Maximum length to fetch',
              },
              start_index: {
                type: 'number',
                description: 'Used together with max_length to retrieve contents piece by piece',
              },
            },
            required: ['url'],
          },
        },
        {
          name: 'fetch_txt',
          description: 'Fetch a website and return the content as plain text (no HTML)',
          inputSchema: {
            type: 'object',
            properties: {
              url: {
                type: 'string',
                description: 'URL of the website to fetch',
              },
              headers: {
                type: 'object',
                description: 'Custom headers to include in the request',
              },
              max_length: {
                type: 'number',
                description: 'Maximum length to fetch',
              },
              start_index: {
                type: 'number',
                description: 'Used together with max_length to retrieve contents piece by piece',
              },
            },
            required: ['url'],
          },
        },
      ],
    }));

    this.server.setRequestHandler(CallToolRequestSchema, async (request) => {
      const { name, arguments: args } = request.params;

      try {
        switch (name) {
          case 'fetch_html':
            return await this.fetchContent(args.url, args.headers, args.max_length, args.start_index, 'html');
          case 'fetch_json':
            return await this.fetchContent(args.url, args.headers, args.max_length, args.start_index, 'json');
          case 'fetch_txt':
            return await this.fetchContent(args.url, args.headers, args.max_length, args.start_index, 'text');
          default:
            throw new McpError(ErrorCode.MethodNotFound, `Unknown tool: ${name}`);
        }
      } catch (error) {
        return {
          content: [
            {
              type: 'text',
              text: `Error: ${error.message}`,
            },
          ],
          isError: true,
        };
      }
    });
  }

  async fetchContent(url, headers = {}, maxLength = DEFAULT_LIMIT, startIndex = 0, format) {
    const fetchOptions = {
      headers: {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
        ...headers,
      },
    };

    const response = await fetch(url, fetchOptions);
    
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }

    let content = await response.text();
    
    // Apply length limits
    const actualMaxLength = maxLength || DEFAULT_LIMIT;
    const actualStartIndex = startIndex || 0;
    
    if (actualStartIndex > 0 || content.length > actualMaxLength) {
      content = content.substring(actualStartIndex, actualStartIndex + actualMaxLength);
    }

    // Process content based on format
    if (format === 'json') {
      try {
        const jsonData = JSON.parse(content);
        content = JSON.stringify(jsonData, null, 2);
      } catch (error) {
        throw new Error('Failed to parse JSON content');
      }
    } else if (format === 'text') {
      // Remove HTML tags for plain text
      content = content.replace(/<[^>]*>/g, '');
      // Clean up extra whitespace
      content = content.replace(/\s+/g, ' ').trim();
    }

    return {
      content: [
        {
          type: 'text',
          text: content,
        },
      ],
    };
  }

  async run() {
    const transport = new StdioServerTransport();
    await this.server.connect(transport);
    console.error('Fetch MCP Server running on stdio');
  }
}

const server = new FetchServer();
server.run().catch(console.error);
