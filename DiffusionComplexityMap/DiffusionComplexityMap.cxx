#include "itkImageFileWriter.h"

#include "itkDiffusionComplexityMappingImageFilter.h"

#include "itkPluginUtilities.h"

#include "DiffusionComplexityMapCLP.h"

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace
{

template <typename TPixel>
int DoIt( int argc, char * argv[], TPixel )
{
  PARSE_ARGS;

  const unsigned int InputDimension = 3;
  const unsigned int OutputDimension = 3;

  typedef float                                         PixelType;
  typedef itk::VectorImage<PixelType, InputDimension>   InputImageType;
  typedef itk::Image<unsigned char, InputDimension>     InputMaskType;
  typedef itk::Image<PixelType, OutputDimension>        OutputImageType;

  typedef itk::ImageFileReader<InputImageType> ReaderType;
  typedef itk::ImageFileReader<InputMaskType> ReaderMaskType;
  typedef itk::ImageFileWriter<OutputImageType> WriterType;
  typedef itk::ImageFileWriter<InputImageType> VectorWriterType;

  ReaderType::Pointer reader = ReaderType::New();
  ReaderMaskType::Pointer readerMask = ReaderMaskType::New();
  reader->SetFileName(inputVolume.c_str());
  readerMask->SetFileName(maskVolume.c_str());
  reader->Update();
  readerMask->Update();

  // cout<<"reader output region: "<<reader->GetOutput()->GetRequestedRegion()<<endl:
  // cout<<" Number of Components: "<<reader->GetOutput()->GetNumberOfComponentsPerPixel()<<endl;

  typedef itk::DiffusionComplexityMappingImageFilter<InputImageType>  FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(reader->GetOutput());
  filter->SetDiffusionSpace(readerMask->GetOutput());
  
  // Set histogram bins
  if (useManualNumberOfBins){
    filter->UseManualNumberOfBinsOn();
    filter->SetHistogramBins(numberOfBins);
  }

  // Set the Q Value
  filter->SetQValue(q);

  // Set the Disequilibrium function
  if (desiquilibriumFunction=="Euclidean"){
    filter->SetDisequilibriumFunction(1);
  }else if (desiquilibriumFunction=="Wooter"){
    filter->SetDisequilibriumFunction(2);
  }else if (desiquilibriumFunction=="Kullback-Leiber"){
    filter->SetDisequilibriumFunction(3);
  }else if (desiquilibriumFunction=="Jensen"){
    filter->SetDisequilibriumFunction(4);
  }

  filter->DebugModeOn();
  filter->Update();

  // cout<<"Filter output region: "<<filter->GetOutput()->GetRequestedRegion()<<endl;
  // cout<<"Filter Number of Components: "<<filter->GetOutput()->GetNumberOfComponentsPerPixel()<<endl;

  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputVolume.c_str());
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;


  // typedef TPixel InputPixelType;
  // typedef TPixel OutputPixelType;

  // const unsigned int Dimension = 3;

  // typedef itk::Image<InputPixelType,  Dimension> InputImageType;
  // typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

  // typedef itk::ImageFileReader<InputImageType>  ReaderType;

  // typename ReaderType::Pointer reader = ReaderType::New();

  // reader->SetFileName( inputVolume.c_str() );

  // typedef itk::SmoothingRecursiveGaussianImageFilter<
  //   InputImageType, OutputImageType>  FilterType;
  // typename FilterType::Pointer filter = FilterType::New();
  // filter->SetInput( reader->GetOutput() );
  // filter->SetSigma( sigma );

  // typedef itk::ImageFileWriter<OutputImageType> WriterType;
  // typename WriterType::Pointer writer = WriterType::New();
  // writer->SetFileName( outputVolume.c_str() );
  // writer->SetInput( filter->GetOutput() );
  // writer->SetUseCompression(1);
  // writer->Update();

  // return EXIT_SUCCESS;
}

} // end of anonymous namespace

int main( int argc, char * argv[] )
{
  PARSE_ARGS;

  itk::ImageIOBase::IOPixelType     pixelType;
  itk::ImageIOBase::IOComponentType componentType;

  try
    {
    itk::GetImageType(inputVolume, pixelType, componentType);

    // This filter handles all types on input, but only produces
    // signed types
    switch( componentType )
      {
      case itk::ImageIOBase::UCHAR:
        return DoIt( argc, argv, static_cast<unsigned char>(0) );
        break;
      case itk::ImageIOBase::CHAR:
        return DoIt( argc, argv, static_cast<signed char>(0) );
        break;
      case itk::ImageIOBase::USHORT:
        return DoIt( argc, argv, static_cast<unsigned short>(0) );
        break;
      case itk::ImageIOBase::SHORT:
        return DoIt( argc, argv, static_cast<short>(0) );
        break;
      case itk::ImageIOBase::UINT:
        return DoIt( argc, argv, static_cast<unsigned int>(0) );
        break;
      case itk::ImageIOBase::INT:
        return DoIt( argc, argv, static_cast<int>(0) );
        break;
      case itk::ImageIOBase::ULONG:
        return DoIt( argc, argv, static_cast<unsigned long>(0) );
        break;
      case itk::ImageIOBase::LONG:
        return DoIt( argc, argv, static_cast<long>(0) );
        break;
      case itk::ImageIOBase::FLOAT:
        return DoIt( argc, argv, static_cast<float>(0) );
        break;
      case itk::ImageIOBase::DOUBLE:
        return DoIt( argc, argv, static_cast<double>(0) );
        break;
      case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
      default:
        std::cerr << "Unknown input image pixel component type: ";
        std::cerr << itk::ImageIOBase::GetComponentTypeAsString( componentType );
        std::cerr << std::endl;
        return EXIT_FAILURE;
        break;
      }
    }

  catch( itk::ExceptionObject & excep )
    {
    std::cerr << argv[0] << ": exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
