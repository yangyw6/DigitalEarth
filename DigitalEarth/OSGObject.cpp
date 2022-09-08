#include "pch.h"
#include "OSGObject.h"

COSGObject::COSGObject(HWND hWnd)
{
	m_hWnd = hWnd;
}

COSGObject::~COSGObject()
{
}

void COSGObject::InitOSG()
{
	InitSceneGraphy();
	InitCameraConfig();
}

void COSGObject::InitSceneGraphy()
{
	mRoot = new osg::Group;
	mRoot->addChild(osgDB::readNodeFile("glider.osg"));
}

void COSGObject::InitCameraConfig()
{
	RECT rect;
	mViewer = new osgViewer::Viewer;
	::GetWindowRect(m_hWnd, &rect);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits);

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height),1.0,1000.0);

	mViewer->setCamera(camera);
	mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	mViewer->setSceneData(mRoot);
	mViewer->realize();
	mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	mViewer->getCamera()->setNearFarRatio(0.000003f);

}

void COSGObject::PreFrameUpdate()
{

}

void COSGObject::PostFrameUpdate()
{
}

void COSGObject::Render(void* ptr)
{
	COSGObject* osg = (COSGObject*)ptr;
	osgViewer::Viewer* viewer = osg->getViewer();
	while (!viewer->done())
	{
		osg->PreFrameUpdate();
		viewer->frame();
		osg->PostFrameUpdate();
	}

	_endthread();
}

osgViewer::Viewer* COSGObject::getViewer()
{
	return mViewer;
}