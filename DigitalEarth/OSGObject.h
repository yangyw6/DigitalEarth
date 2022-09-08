#pragma once

#include <osgViewer/Viewer>
#include <osgDB/Readfile>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>


class COSGObject
{
public:
	COSGObject(HWND hWnd);
	~COSGObject();

	void InitOSG();
	void InitSceneGraphy();
	void InitCameraConfig();
	void PreFrameUpdate();
	void PostFrameUpdate();
	static void Render(void* ptr);

	osgViewer::Viewer* getViewer();

private:
	HWND m_hWnd;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;

};

