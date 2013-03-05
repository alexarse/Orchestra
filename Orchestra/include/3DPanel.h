#ifndef DEF_3DPANEL_H
#define DEF_3DPANEL_H

#include "axLib.h"
#include "irrlicht.h"

class mIrrDevice;
class mIrrWindow;

typedef irr::SIrrlichtCreationParameters m3d_CreateParam;
typedef irr::video::E_DRIVER_TYPE        m3d_DriverType;
typedef irr::IrrlichtDevice              m3d_Device;
typedef irr::scene::ISceneManager        m3d_SceneManager;
typedef irr::video::IVideoDriver         m3d_VideoDriver;
typedef irr::scene::ICameraSceneNode     m3d_Camera;
typedef irr::scene::ISceneNode           m3d_Node;
typedef irr::video::SColor               m3d_Color;
typedef irr::core::dimension2d<irr::s32> m3d_Dimension2D;
typedef irr::core::vector3df             m3d_Vector3D;
typedef irr::video::E_MATERIAL_FLAG      m3d_MaterialFlag;
typedef irr::s32                         m3d_S32;

#endif