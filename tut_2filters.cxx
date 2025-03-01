// Example 4: do a contour and a clip-with-field, and write it out.
//
#include <vtkm/io/reader/VTKDataSetReader.h>
#include <vtkm/io/writer/VTKDataSetWriter.h>
#include <vtkm/filter/Contour.h>
#include <vtkm/filter/ClipWithField.h>


int main()
{
  const char *input = "kitchen.vtk";
  vtkm::io::reader::VTKDataSetReader reader(input);
  vtkm::cont::DataSet ds_from_file = reader.ReadDataSet();

  vtkm::filter::Contour contour;
  contour.SetActiveField("c1");
  contour.SetFieldsToPass({ "c1", "ke" });
  contour.SetNumberOfIsoValues(3);
  contour.SetIsoValue(0, 0.05);
  contour.SetIsoValue(1, 0.10);
  contour.SetIsoValue(2, 0.15);
  vtkm::cont::DataSet ds_from_mc = contour.Execute(ds_from_file);

  vtkm::filter::ClipWithField clip;
  clip.SetActiveField("ke");
  clip.SetClipValue(1e-7);
  //clip.SetInvertClip(true); // <1e-7 instead of >1e-7

  vtkm::cont::DataSet ds_from_clip = clip.Execute(ds_from_mc);

  vtkm::io::writer::VTKDataSetWriter writer("out_2filters.vtk");
  writer.WriteDataSet(ds_from_clip);

  return 0;
}
