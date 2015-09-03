#include<iostream>
#include<vector>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(void)
{


	char line_string[500];

	ofstream wgetfile("wget_images.sh");


	ifstream archive_texture_pages("archive_pages.txt");

	while(1)
	{
		archive_texture_pages.getline(line_string,500);

		if ( archive_texture_pages.eof() ) 
			break;

		std::string webpage = std::string("archivetextures.net/") + std::string(line_string);

		webpage = std::string("wget ") + std::string(webpage) + std::string(" -O archive_tex.html");

		std::cout << webpage << std::endl;
		
		system(webpage.c_str());
		//continue;

		int i =2;	
		int count=0;
	
	while(1)
	{
		
		char fileName[400];
		
		sprintf(fileName,"grep -R \"?a=download\" archive_tex.html | sed 's/<\\/a><\\/div><div>/\\r/g' | cut -f%d -d'\"' > download_link.txt",i);

		//std::cout<<fileName<<std::endl;

		system(fileName);
		
		ifstream ifile("download_link.txt");

		ifile.getline(line_string,100);

		ifile.close();

		std::string line_str(line_string);

		if ( line_str.empty() )
			break;
		
		std::cout<<line_string<<std::endl;

		std::string link = std::string("google-chrome \"archivetextures.net") + std::string(line_string) + std::string("\" &");


		system(link.c_str());

		usleep(2e6);
		link = std::string("xdotool mousemove 500 460 click 1\n");
		system(link.c_str());		
		usleep(4e6);
		system("xdotool mousemove 800 500 click 1");		
		usleep(6e6);
		system("xdotool mousemove 600 60 click 1");		
		system("xdotool key --clearmodifiers \"ctrl+c\"");// 600 50 click 1");		

		
		system("xsel > image.txt");

		system("xdotool key --clearmodifiers \"ctrl+w\"");

		ifstream imgFile("image.txt");
		imgFile.getline(line_string,300);
		imgFile.close();

		line_str = std::string(line_string);
		
		sprintf(fileName,"grep -R \"?a=download\" archive_tex.html | sed 's/<\\/a><\\/div><div>/\\r/g' | cut -f%d -d'\"' | cut -f2 -d\":\" | cut -f2 -d' ' > matname.txt",i+2);
		system(fileName);
		ifstream matName("matname.txt");
		matName.getline(line_string,100);
		
		std::string materialName(line_string);	
		matName.close();
		
		
		if ( !line_str.empty() )
		{
			wgetfile << "wget " << line_str<<" "<< materialName << std::endl;
		}

		std::cout <<link<<std::endl;

		//DIR* dir = opendir(materialName.c_str());
	
		struct stat sb;
	
		if (stat(materialName.c_str(),&sb)==0 
		    && S_ISDIR(sb.st_mode) )
		{
		}
		else
		{
			std::string mkDir = std::string("mkdir ") + std::string(materialName);
			system(mkDir.c_str());
		}
		//closedir(dir);

//		if ( count >=2 )
//			break;
				
		i+=10;

		count++;
		
	}

	}
	
	archive_texture_pages.close();

	wgetfile.close();

}
