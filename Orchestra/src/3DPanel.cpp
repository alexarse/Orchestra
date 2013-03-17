/// @todo Needs Documentation Header.
#include "3DPanel.h"
#include <windows.h>
#include <cmath>

BEGIN_EVENT_TABLE(Device3D, wxWindow)
   EVT_PAINT(Device3D::OnPaint)
   EVT_LEFT_UP(Device3D::OnMouseLeftUp)
   EVT_MOTION(Device3D::OnMouseMotion)
   EVT_LEFT_DOWN(Device3D::OnMouseLeftDown)
END_EVENT_TABLE()


Device3D::Device3D(wxWindow* win, irr_DriverType type, bool bResizeable)
		   : wxWindow(win, wxID_ANY, wxPoint(0, 0), wxSize(500, 500))
{
	irr_CreateParam param;
	
	//Window Only
	param.WindowId = reinterpret_cast<void *> ((HWND) this->GetHandle());
	param.DriverType = type;
	param.Doublebuffer = true;
	param.WindowSize = irr_Dimension2D(500, 500);

	irrDevice = irr::createDeviceEx(param);

	theta = M_PI * 0.5;
	camera_ = AddCamera(0, irr_Vector3D(cos(theta) * 1.8, 2.0f, sin(theta) * 1.8), irr_Vector3D(0.0f, 2.0f, 0.0f));

	irr_Mesh* mesh = GetSceneManager()->getMesh("resources/male.x");
	irr_SceneMesh* node = GetSceneManager()->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setJointMode(irr::scene::EJUOR_CONTROL);
		node->setPosition(irr_Vector3D(0, -5, -5));
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, true);
		node->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, true);
		node->setRotation(irr_Vector3D(180, 180, 0));
		node->setScale(irr_Vector3D(0.65, 0.65, 0.65));
			
		node->setMaterialTexture(0, irrDevice->getVideoDriver()->getTexture("resources/male_c.png"));

		// Afficher tous les bones.
		_DEBUG_		irr_Bone* bone;
		_DEBUG_		for(int i = 0; i < node->getJointCount(); ++i)
		_DEBUG_		{
		_DEBUG_			bone = node->getJointNode(i);
		_DEBUG_			_DEBUG_ DSTREAM << "BONE NAME : " << bone->getName() << endl;
		_DEBUG_		}

		hand_		= node->getJointNode("pc_rig_hand_L");
		hips_		= node->getJointNode("pc_rig_hips");
		forearm_L	= node->getJointNode("pc_rig_forearm_L");
		upper_arm_L = node->getJointNode("pc_rig_upper_arm_L");

		node->animateJoints();

		//Compute(hand_, (irr_Bone*) upper_arm_L->getParent(), hand_->getPosition());
		hips_->setRotation(irr_Vector3D(0, 0, 0));
		upper_arm_L->setRotation(upper_arm_L->getRotation() + irr_Vector3D(20, 20, 40));
		//hand_->setRotation(hand_->getRotation() + irr_Vector3D(-5, -10, -10));
	}

	////window->SetDevice(this);
	if(irrDevice) irrDevice->setResizable(bResizeable);
}

Device3D::~Device3D()
{
	if(irrDevice)
	{
		irrDevice->closeDevice();
		irrDevice->drop();
	}
}

irr_Camera* Device3D::AddCamera(irr_Node* parent, irr_Vector3D& position, irr_Vector3D& lookat, irr_S32 id)
{
   irr_SceneManager* irrSceneMgr = GetSceneManager();
	
   if (irrSceneMgr)
	  return (irr_Camera*) irrSceneMgr->addCameraSceneNode(parent, position, lookat);
   else
	  return NULL;	
}

void Device3D::OnMouseLeftUp(wxMouseEvent& event)
{
	if(HasCapture())
	{
		ReleaseMouse();
	}
}
void Device3D::OnMouseMotion(wxMouseEvent& event)
{
	int x = event.GetX() - clickPt.x;
	int y = event.GetY() - clickPt.y;

	if(event.Dragging() && HasCapture() && event.LeftIsDown())
	{
		irr_Vector3D rot = upper_arm_L->getRotation() + irr_Vector3D(x, y, 0);

		if(rot.X < 280)	rot.X = 280;
		if(rot.X > 405)	rot.X = 405;

		if(rot.Y < -30)	rot.Y = -30;
		if(rot.Y > 66)	rot.Y = 66;

		upper_arm_L->setRotation(rot);

		_DEBUG_ DSTREAM << "VECTOR : " << rot.X << ", " << rot.Y << ", " << rot.Z << endl;

		//_DEBUG_ DSTREAM << "MOTION" << endl;
		//theta += (x - clickPts_x) * -0.0002;

		//if(theta > 2.0 * M_PI)	theta -= (2.0 * M_PI);
		//if(theta < -2.0 * M_PI)	theta += (2.0 * M_PI);
		//
		//// NE FONCTIONNE PAS (PROBABLEMENT A CAUSE DU : node->setRotation(irr_Vector3D(180, 180, 0)); 
		//// DANS LE CONSTRUCTEUR
		//camera_->setPosition(irr_Vector3D(cos(theta) * 1.8, 1.2f, sin(theta) * 1.8));
		//_DEBUG_ DSTREAM << "LEFT : " << cos(theta) * 1.8 << " , Right : " << sin(theta) * 1.8 << endl;

		Refresh();
	}
}
void Device3D::OnMouseLeftDown(wxMouseEvent& event)
{	
	clickPt = event.GetPosition();
	_DEBUG_ DSTREAM << "LEFT DOWN" << endl;
	CaptureMouse();
}

void Device3D::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);

	_DEBUG_ DSTREAM << "PAINT TEST" << endl;

	if(irrDevice)
	{
		irr_VideoDriver* driver = irrDevice->getVideoDriver();
		irr_SceneManager* scenemgr = irrDevice->getSceneManager();

		//forearm_L->setRotation(forearm_L->getRotation() + irr_Vector3D(0, 0, 0));
		//hand_->setRotation(hand_->getRotation() + irr_Vector3D(0, 0, 0));
		//upper_arm_L->updateAbsolutePosition();
		//upper_arm_L->updateAbsolutePositionOfAllChildren();

		//_DEBUG_ DSTREAM << "UPPER   (Parent) : " << upper_arm_L->getParent()->getName() << endl;
		//_DEBUG_ DSTREAM << "FOREARM (Parent) : " << forearm_L->getParent()->getName() << endl;
		//_DEBUG_ DSTREAM << "HAND    (Parent) : " << hand_->getParent()->getName() << endl;

		if(driver)
		{
			 driver->beginScene(true, true, irr_Color(200, 80, 80, 80));

			if(scenemgr) scenemgr->drawAll();

			driver->endScene();
		}
	}
}

// http://irrlicht.sourceforge.net/forum/viewtopic.php?t=43514
bool Device3D::Compute(irr_Bone* boneNode, irr_Bone* rootBoneNode, irr_Vector3D target)
{
    irr_Vector3D rootPos, curEnd, targetVector, desiredEnd, curVector, crossResult, endPos = target;
    double cosAngle,turnAngle;
    irr_Bone* link;
    irr_Bone* end;

    // start at the last link in the chain
    end = boneNode;
    link = (irr_Bone*)end->getParent();
    int tries = 0;
    double norm = 2;

    int maxTries = 1000;
    double error = 0.1;
    double maxAngleChange = M_PI / 12.0;

    while (++tries < maxTries && norm > 0.1)
    {
        link->updateAbsolutePosition();
        end->updateAbsolutePosition();

        rootPos = link->getAbsolutePosition();
        curEnd = end->getAbsolutePosition();
        desiredEnd = endPos;
        norm = curEnd.getDistanceFromSQ(desiredEnd);

        //std::cout << norm << std::endl;

        // see if i'm already close enough
        if (norm > error)
        {
            // create the vector to the current effector pos
            curVector = curEnd - rootPos;
            // create the desired effector position vector
            targetVector = endPos - rootPos;

            // normalize the vectors (expensive, requires a sqrt)
            curVector.normalize();
            targetVector.normalize();

            // the dot product gives me the cosine of the desired angle
            cosAngle = curVector.dotProduct(targetVector);
            // if the dot product returns 1.0, i don't need to rotate as it is 0 degrees
            if (cosAngle < 0.9999999)
            {
                // use the cross product to check which way to rotate
                crossResult = curVector.crossProduct(targetVector);

                crossResult.normalize();
                turnAngle = acos(cosAngle);   // get the angle

                if(turnAngle < maxAngleChange)
                {
                    turnAngle = maxAngleChange;
                }

                irr_quatornion rotation;
                rotation = rotation.fromAngleAxis(turnAngle, crossResult);
                rotation.normalize();
                irr_Vector3D euRotation;
                rotation.toEuler(euRotation);
                link->setRotation(link->getRotation() + irr_Vector3D(euRotation.Z, euRotation.X, euRotation.Y));

                //TODO: check DOF restrictions for link joint here.
            }

            if (link == rootBoneNode)
            {
                link = (irr_Bone*)end->getParent();   // start of the chain, restart
            }
            else
            {
                link = (irr_Bone*)link->getParent();
            }
        }
    }

    if (tries == maxTries)
    {
        return false;
    }

    return true;
}