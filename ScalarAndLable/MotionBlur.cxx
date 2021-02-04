#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOpenGLRenderer.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderStepsPass.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSimpleMotionBlurPass.h>
#include <vtkTextureObject.h>

#include <vtkSTLReader.h>
#include <array>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPointData.h>
#include <vtkNamedColors.h>
#include <vtkColorTransferFunction.h>

#define vSP vtkSmartPointer
#define vSPNew(Var, Type) vSP<Type> Var = vSP<Type>::New();
#include <iostream>
void ScalarSetting()
{

}
//----------------------------------------------------------------------------
int main(int, char* argv[])
{
  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(0,0,1);

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetSize(500, 500);
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("MotionBlur");

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renderWindow);

  vtkNew<vtkSTLReader> reader;
  reader->SetFileName("E://VtkTest/buildScalar/Release/deci.stl");
  reader->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(reader->GetOutputPort());

  int ptsCount = reader->GetOutput()->GetNumberOfPoints();

  vSPNew(scalars, vtkIntArray);
  scalars->SetNumberOfTuples(ptsCount);

  for (int i = 0; i < ptsCount; ++i)
  {
      scalars->SetTuple1(i, i);
      i ++;
  }
  reader->GetOutput()->GetPointData()->SetScalars(scalars);

  vSPNew(lut, vtkColorTransferFunction);
  lut->SetClamping(0);
  vSPNew(colors, vtkNamedColors);
  std::cout << "2222" << std::endl;
  std::string colorNames[8] = { "Gray", "Black", "Red", "Maroon", "Yellow", "Lime", "Green", "Blue" };
  for (int i = 0; i < ptsCount; )
  {
      double color[3];
      colors->GetColorRGB(colorNames[i%8].c_str(), color);
      lut->AddRGBPoint(i, color[0], color[1], color[2]);
      i ++;
  }
  std::cout << "2222Over" << std::endl;
  mapper->SetScalarModeToUsePointData();
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, ptsCount);
  // create three models
  {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
   // actor->GetProperty()->SetAmbientColor(colors->GetColor3d("Red").GetData());
   // actor->GetProperty()->SetDiffuseColor(
    //    colors->GetColor3d("A1Diff").GetData());
   // actor->GetProperty()->SetSpecular(0.0);
    //actor->GetProperty()->SetDiffuse(0.5);
    //actor->GetProperty()->SetAmbient(0.3);
    actor->SetPosition(-0.1, 0.0, -0.1);
    renderer->AddActor(actor);
  }




  renderWindow->SetMultiSamples(0);

  // create the basic VTK render steps
  //vtkNew<vtkRenderStepsPass> basicPasses;

  //vtkNew<vtkSimpleMotionBlurPass> motion;
  //motion->SetDelegatePass(basicPasses);

  //// tell the renderer to use our render pass pipeline
  //vtkOpenGLRenderer* glrenderer =
  //    dynamic_cast<vtkOpenGLRenderer*>(renderer.GetPointer());
  //glrenderer->SetPass(motion);

  //int numRenders = 30;

  //renderer->GetActiveCamera()->SetPosition(0, 0, -1);
  //renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  //renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
  //renderer->ResetCamera();
  //renderer->GetActiveCamera()->Azimuth(15.0);
  //renderer->GetActiveCamera()->Zoom(1.2);

  //renderWindow->Render();

  //for (int i = 0; i < numRenders; ++i)
  //{
  //  renderer->GetActiveCamera()->Azimuth(10.0 / numRenders);
  //  renderer->GetActiveCamera()->Elevation(10.0 / numRenders);
  //  renderWindow->Render();
  //}
  std::cout << "1111" << std::endl;
  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}