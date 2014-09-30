#ifndef __UMODEL_APP_H__
#define __UMODEL_APP_H__

#include "Viewers/ObjectViewer.h"
#include "UmodelSettings.h"

class CUmodelApp : public CApplication
{
public:
	CUmodelApp();
	~CUmodelApp(); //?? virtual?

	virtual void WindowCreated();
	virtual void Draw3D(float TimeDelta);
	virtual void DrawTexts(bool helpVisible);
	virtual void BeforeSwap();
	virtual void ProcessKey(int key, bool isDown);

#if RENDERING
	bool CreateVisualizer(UObject *Obj, bool test = false);
	// dir = 1 - forward direction for search, dir = -1 - backward.
	// When forceVisualizer is true, dummy visualizer will be created if no supported object found
	bool FindObjectAndCreateVisualizer(int dir, bool forceVisualizer = false, bool newPackage = false);

	FORCEINLINE bool ObjectSupported(UObject *Obj)
	{
		return CreateVisualizer(Obj, true);
	}
#else // RENDERING
	FORCEINLINE bool ObjectSupported(UObject *Obj)
	{
		return true;
	}
#endif // RENDERING

#if HAS_UI
	bool ShowStartupDialog(UmodelSettings& settings);
	bool ShowPackageUI();
#endif

#if RENDERING
	CObjectViewer *Viewer;			// used from GlWindow callbacks
	int			ObjIndex;			// index of the current object in UObject::GObjObjects array
	bool		ShowMeshes;
	bool		ShowMaterials;
#endif
};

extern CUmodelApp GApplication;

void InitClassAndExportSystems(int Game);
bool ExportObjects(const TArray<UObject*> *Objects = NULL, IProgressCallback* progress = NULL);
void DisplayPackageStats(const TArray<UnPackage*> &Packages);


#endif // __UMODEL_APP_H__
