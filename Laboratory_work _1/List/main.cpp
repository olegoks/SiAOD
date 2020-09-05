#include <iostream>
#include "ListType.h"

int main(int argc, char* argv[])
{
	{
		using namespace nmspc;
		try {

			List<int> list;
			list.push_back(1);
			list.push_back(111);
			list.push_back(123);
			list.insert(1, 1000);
			list.erase(6);
			for (size_t i = 0; i < list.size(); i++) std::cout << list[i] << std::endl;
			
		}
		catch (List<int>::ListException error) {

			std::cerr <<"Error:" << error.GetError() << std::endl;

		}

	}

	system("pause");

}


