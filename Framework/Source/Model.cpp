//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Model.h"
#include "Animation.h"
#include "World.h"
#include "ParticleEmitter.h"
#include "ParticleDescriptor.h"
#include "ParticleSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Model::Model() 
	: mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f), 
	  mRotationAngleInDegrees(0.0f), mAnimation(nullptr), mParticleSystem(nullptr)
{
}

Model::~Model()
{
	if (mParticleSystem)
    {
        World::GetInstance()->RemoveParticleSystem(mParticleSystem);
        delete mParticleSystem;
    }
}

void Model::Update(float dt)
{
}

void Model::Draw()
{
}

void Model::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0].c_str());
			getchar();
			exit(-1);
		}
	}
}

bool Model::ParseLine(const std::vector<ci_string> &token)
{
		if (token.empty() == false)
	{
		if (token[0].empty() == false && token[0][0] == '#')
		{
			return true;
		}
		else if (token[0] == "name")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			mName = token[2];	
		}
		else if (token[0] == "position")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mPosition.x = static_cast<float>(atof(token[2].c_str()));
			mPosition.y = static_cast<float>(atof(token[3].c_str()));
			mPosition.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "rotation")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mRotationAxis.x = static_cast<float>(atof(token[2].c_str()));
			mRotationAxis.y = static_cast<float>(atof(token[3].c_str()));
			mRotationAxis.z = static_cast<float>(atof(token[4].c_str()));
			mRotationAngleInDegrees = static_cast<float>(atof(token[5].c_str()));

			glm::normalize(mRotationAxis);
		}
		else if (token[0] == "scaling")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mScaling.x = static_cast<float>(atof(token[2].c_str()));
			mScaling.y = static_cast<float>(atof(token[3].c_str()));
			mScaling.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "animation")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			ci_string animName = token[2];
            
            mAnimation = World::GetInstance()->FindAnimation(animName);
			mAnimation->setCurrentModel(this);
		}
		else if (token[0] == "direction"){
			assert(token.size() > 4);
			assert(token[1] == "=");

			mStretchVec.x = static_cast<float>(atof(token[2].c_str()));
			mStretchVec.y = static_cast<float>(atof(token[3].c_str()));
			mStretchVec.z = static_cast<float>(atof(token[4].c_str()));
			normalize(mStretchVec);
		}
		else if (token[0] == "range"){
			assert(token.size() > 4);
			assert(token[1] == "=");
			assert(token[3] == "/");

			rangeNumerator = static_cast<int>(atof(token[2].c_str()));
			rangeDenominator = static_cast<int>(atof(token[4].c_str()));
		}
		else if (token[0] == "particlesystem")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");
			assert(token[2] == "\"fire\"" || token[2] == "\"fountain\"" || "\"stars\""); // only to hardcoded particle systems


			ParticleEmitter* emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f), this);
			ParticleDescriptor* desc = new ParticleDescriptor();

			if (token[2] == "\"fire\"")
			{
				desc->SetFireDescriptor();
			}
			else if (token[2] == "\"fountain\"")
			{
				desc->SetFountainDescriptor();
			}
			else if (token[2] == "\"stars\"")
			{
				desc->SetStarsDescriptor();
			}

			mParticleSystem = new ParticleSystem(emitter, desc);
			World::GetInstance()->AddParticleSystem(mParticleSystem);
		}
		else
		{
			return false;
		}
	}

	return true;
}

glm::mat4 Model::GetWorldMatrix() const
{
	mat4 worldMatrix;

	if (mAnimation != nullptr){
		worldMatrix = (*mAnimation).GetAnimationWorldMatrix(mPosition, mScaling, mStretchVec, rangeNumerator, rangeDenominator);
	}
	else{
		worldMatrix = translate(mat4(1.0f), mPosition) * rotate(mat4(1.0f), mRotationAngleInDegrees, mRotationAxis) * scale(mat4(1.0f), mScaling);
	}

	return worldMatrix;
}

glm::vec3 Model::GetPosition() const { return mPosition; }
glm::vec3 Model::GetColor() const { return mColor; }

void Model::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void Model::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void Model::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}
