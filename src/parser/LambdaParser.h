#pragma once
#include "../exp_hierarchy/auto_load.hh"

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
				//INIT
				Functor::initBaseFunctions();
				Functor::gCodeBegin();
				return parser.parse();
			}
		private:
			Lambda::FlexScanner scanner;
			Lambda::BisonParser parser;
	};
} 
