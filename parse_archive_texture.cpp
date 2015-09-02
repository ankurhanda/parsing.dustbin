#include<iostream>
#include<vector>
#include <stdlib.h>
#include <fstream>


using namespace std;

int main(void)
{

	int i =2;	

	char line_string[100];

	while(1)
	{
		
		char fileName[400];
		
		sprintf(fileName,"grep -R \"?a=download\" archive_tex.html | sed 's/<\\/a><\\/div><div>/\\r/g' | cut -f%d -d'\"' > download_link.txt",i);

		std::cout<<fileName<<std::endl;

		system(fileName);
		
		ifstream ifile("download_link.txt");

		ifile.getline(line_string,100);

		

		std::cout<<line_string<<std::endl;

		ifile.close();

		std::string line_str(line_string);

		if ( line_str.empty() )
			break;
		
		i+=10;
		
	}

}
