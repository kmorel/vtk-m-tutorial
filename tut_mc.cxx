// Example 2: do a contour!, write it out.
//
#include <vtkm/io/reader/VTKDataSetReader.h>
#include <vtkm/io/writer/VTKDataSetWriter.h>
#include <vtkm/filter/Contour.h>


int main()
{
  const char *input = "kitchen.vtk";
  vtkm::io::reader::VTKDataSetReader reader(input);
  vtkm::cont::DataSet ds_from_file = reader.ReadDataSet();

  vtkm::filter::Contour contour;
  contour.SetActiveField("c1");
  contour.SetNumberOfIsoValues(3);
  contour.SetIsoValue(0, 0.05);
  contour.SetIsoValue(1, 0.10);
  contour.SetIsoValue(2, 0.15);

  vtkm::cont::DataSet ds_from_mc = contour.Execute(ds_from_file);
  vtkm::io::writer::VTKDataSetWriter writer("out_mc.vtk");
  writer.WriteDataSet(ds_from_mc);

  return 0;
}
