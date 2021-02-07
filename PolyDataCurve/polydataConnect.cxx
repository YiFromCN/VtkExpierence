#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkSTLReader.h>
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>

int main()
{
	vtkSmartPointer<vtkSTLReader> reader =
		vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName("E://VtkTest/buildScalar/Release/deci.stl");
	reader->Update();


	vtkSmartPointer<vtkCurvatures> curvaturesFilter =
		vtkSmartPointer<vtkCurvatures>::New();
	curvaturesFilter->SetInputConnection(reader->GetOutputPort());
	curvaturesFilter->SetCurvatureTypeToGaussian();
	curvaturesFilter->Update();


	double scalarRange[2];
	curvaturesFilter->GetOutput()->GetScalarRange(scalarRange);


	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetHueRange(0.0, 0.6);
	lut->SetAlphaRange(1.0, 1.0);
	lut->SetValueRange(1.0, 1.0);
	lut->SetSaturationRange(1.0, 1.0);
	lut->SetNumberOfTableValues(256);
	lut->SetRange(-1, 10);
	lut->Build();


	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(curvaturesFilter->GetOutput());
	mapper->SetLookupTable(lut);
	mapper->SetScalarRange(-1,10);


	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);


	vtkSmartPointer<vtkScalarBarActor> scalarBar =
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(mapper->GetLookupTable());
	//scalarBar->SetTitle(
	//	curvaturesFilter->GetOutput()->GetPointData()->GetScalars()->GetName());
	scalarBar->SetNumberOfLabels(6);
	vtkDataArray* dataArry = curvaturesFilter->GetOutput()->GetPointData()->GetAttribute(0);
	vtkDoubleArray vtkDArray = curvaturesFilter->GetOutput().GetPointData().GetAttribute(0).GetNativePointer()
	vtkDoubleArray vtkDArray = new vtkDoubleArray(, true);
	double[] CurvImage = new double[datasize];
	for (int i = 0; i < datasize; i++)
	{
		CurvImage[i] = vtkDArray.GetValue(i);
	}

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->AddActor2D(scalarBar);
	renderer->SetBackground(1.0, 1.0, 1.0);


	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataCurvature");


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);


	renderWindowInteractor->SetInteractorStyle(style);


	renderWindow->Render();
	renderWindowInteractor->Start();


	return EXIT_SUCCESS;
}
