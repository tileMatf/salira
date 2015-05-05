#pragma once

namespace Lambda
{
	class Parser
	{
		public: 	
			Parser()
			:parser(scanner)
			{}

			int parse()
			{
				return parser.parse();
			}
		private:
			Lambda::FlexScanner scanner;
			Lambda::BisonParser parser;
	};
} 
