#include <iostream>
#include <stdio.h>


int main()
{

	FILE* pFile = NULL;
	FILE* pFile2 = NULL;
	char FileName[256];
	int ScaleValue = 0;
	char NewFileName[256];

	//While there is no pFile, run this loop

	while (true)
	{
		std::cout << "Enter File Name (Must be in path directory, do not include file type)" << std::endl;
		//Input for variable FileName
		scanf("%s", FileName);
		//Convert Int FileName to String
		std::string FileNameext = FileName;
		//Add .bmp to the end of the filename
		FileNameext += ".bmp";
		//Open FileName in read binary
		pFile = fopen(FileNameext.c_str(), "rb");

		//If there is no FilePointer (You entered a non existant file Name, Case Sensitive)
		if (!pFile)

		{
			//Print out Error Message
			std::cout << "Error 404: File Not Found" << std::endl;
		}
		else
		{
			//Continue on
			break;
		}


	}



	//Scan through the program and set to send.
	fseek(pFile, 0, SEEK_END);
	//Read file data
	int fileData = ftell(pFile);
	//set back to start of char pointer
	rewind(pFile);

	//Create a Char Filebuffer, this will be where data is viewed.
	char* FileBuffer = new char[fileData];


	std::cout << "File Buffer Created Successfully" << std::endl;

	//fread(Reading Information from pFile and Filesize, and placing into Filebuffer)
	fread(FileBuffer, fileData, 1, pFile);

	//Cast Header Values into Int from FileBuffer
	short headerSignature = *(short*)&FileBuffer[0];
	int ImageSize = *(int*)&FileBuffer[2];
	int ImageOffset = *(int*)&FileBuffer[10]; //ImageOffset = Image Header Size
	int ImageHeight = *(int*)&FileBuffer[22];
	int ImageWidth = *(int*)&FileBuffer[18];
	int BitsPerPixel = *(int*)&FileBuffer[28];


	std::cout << "ImageSize: " << ImageSize << std::endl;
	std::cout << "ImageOffset: " << ImageOffset << std::endl;
	std::cout << "ImageHeight: " << ImageHeight << std::endl;
	std::cout << "ImageWidth: " << ImageWidth << std::endl;
	std::cout << "BitsPerPixel: " << BitsPerPixel << std::endl;



	std::cout << "Enter the amount of times you want to scale the image by (Hint, only 2)" << std::endl;
	std::cin >> ScaleValue;
	std::cout << "\n";


	//Create a New Buffer large enough to fit new image data


	//Determine Original BMP Row Size
	int RowSizeOld = (BitsPerPixel * ImageWidth + 31) / 32 * 4;

	//Modify RowSize and Header Values
	int RowSizeNew = (BitsPerPixel *(ImageWidth * ScaleValue) + 31) / 32 * 4;
	int NewImageSize = ImageOffset + (RowSizeNew * (ScaleValue * ImageHeight));
	int NewImageHeight = ImageHeight * ScaleValue;
	int NewImageWidth = ImageWidth * ScaleValue;
	int NewFileData = RowSizeNew * (ScaleValue * ImageHeight);

	//Create New File Buffer, this will store modified image data
	char* NewFileBuffer = new char[NewImageSize];

	std::cout << "File Buffer being modified..." << std::endl;


	std::cout << " RowSizeOld: " << RowSizeOld << std::endl;
	std::cout << "RowSizeNew: " << RowSizeNew << std::endl;
	std::cout << "NewImageSize: " << NewImageSize << std::endl;
	std::cout << "NewImageHeight: " << NewImageHeight << std::endl;
	std::cout << "NewImageWidth: " << NewImageWidth << std::endl;


	memset(NewFileBuffer, 0, ImageOffset + (RowSizeNew * NewImageHeight));


	//New Header Values
	*(short*)&NewFileBuffer[0] = headerSignature;
	*(int*)&NewFileBuffer[2] = NewImageSize;
	*(int*)&NewFileBuffer[10] = ImageOffset;
	*(int*)&NewFileBuffer[22] = NewImageHeight;
	*(int*)&NewFileBuffer[18] = NewImageWidth;
	*(int*)&NewFileBuffer[28] = BitsPerPixel;
	*(int*)&NewFileBuffer[14] = 40;
	*(short*)&NewFileBuffer[26] = 1;
	*(int*)&NewFileBuffer[34] = NewFileData;


	//For loops go here, Use Pixel Data as a starting reference.
	// These ints define the colour values for RGB and Padding

	//ImageLengthCopy

	int pixel = 54;


	

		for (int InitialPixel = 0; InitialPixel < 6; InitialPixel += 3)
		{

			//This for loop cycles through R, B and G to run the same function.
			for (int pixelPicker = 0; pixelPicker < 3; pixelPicker++)
			{
				//Check how many times the height needs to be run through
				for (int Height = 0; Height < ImageHeight; Height++)
				{
					//Check how many times width needs to be run through
					for (int Width = 0; Width < ImageWidth; Width++)
					{
						//Read Values from Old Buffer into New Buffer and * 2
						NewFileBuffer[pixel +  pixelPicker + InitialPixel + RowSizeNew * (Height * 2) + (Width * 3 * 2) ] = FileBuffer[pixel + pixelPicker + RowSizeOld * (Height)+(Width * 3)];
					}
				}

			}
		}

		

		for (int InitialPixel = 0; InitialPixel < 6; InitialPixel += 3)
		{

			//This for loop cycles through R, B and G to run the same function.
			for (int pixelPicker = 0; pixelPicker < 3; pixelPicker++)
			{
				//Check how many times the height needs to be run through
				for (int Height = 0; Height < ImageHeight; Height++)
				{
					//Check how many times width needs to be run through
					for (int Width = 0; Width < ImageWidth; Width++)
					{
						//Read Values from Old Buffer into New Buffer and * 2
						NewFileBuffer[(pixel + (NewImageWidth * 8)) + pixelPicker + InitialPixel  + RowSizeNew * (Height * 2) + (Width * 3 * 2)] = FileBuffer[(pixel + (ImageWidth * 8)) + pixelPicker +  + RowSizeOld * (Height)+(Width * 3)];
					}
				}

			}
		}


		

		//(ILC * (BitsPerPixel/8)) +
	
	// For Each Time you do ILC, do it + Image Width

					
std::cout << "Enter your new FileName" << std::endl;
scanf  ("%s", NewFileName);


	
	//Create a New File Name
	std::string NewFileNameExt = NewFileName;
	NewFileNameExt += ".bmp";
	pFile2 = fopen(NewFileNameExt.c_str(), "wb");
	fwrite(NewFileBuffer, 1, NewImageSize , pFile2);

return 0;
}








