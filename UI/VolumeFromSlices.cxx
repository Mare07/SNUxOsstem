#include "vol.h"

void make_mha(char *path, int first, int last, char *outputFilename) {
	typedef unsigned char PixelType;
  const unsigned int Dimension = 3;

  typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageSeriesReader< ImageType > ReaderType;
	typedef itk::ImageFileWriter< ImageType > WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	/*
	const unsigned int first = 87;
	const unsigned int last = 185;

	const char *name = "./results/ct.res.%d.jpg";
	const char *outputFilename = "result.mha";
	*/

	typedef itk::NumericSeriesFileNames NameGeneratorType;

	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

	nameGenerator->SetSeriesFormat(path);
	nameGenerator->SetStartIndex(first);
	nameGenerator->SetEndIndex(last);
	nameGenerator->SetIncrementIndex(1);
	std::vector<std::string> names = nameGenerator->GetFileNames();

	reader->SetFileNames(names);
	writer->SetFileName(outputFilename);
	writer->SetInput(reader->GetOutput());

	try {
		writer->Update();
	} catch (itk::ExceptionObject & err) {
		std::cerr << "ExceptionObject caught!" << std::endl;
		std::cerr << err << std::endl;
		return;
	}
	return;
}
