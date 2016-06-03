#include "CMaterial.h"
#include <fstream>
#include "DebugUtilities.h"
#include "CTextureManager.h"

extern CTextureManager* g_pTextureManager;

CMaterial::CMaterial() : CObject(EMaterial){
	m_bCollision = false;
	m_fWalkspeed = 1.0f;
	m_Name = "Unknown";
	m_pTexture = nullptr;
}

CMaterial::CMaterial(std::string name, sf::Texture * texture, bool collision, float walkspeed) : CObject(EMaterial) {
	m_bCollision = collision;
	m_fWalkspeed = walkspeed;
	m_Name		 = name;
	m_pTexture	 = texture;
}

CMaterial::~CMaterial(){
}


CMaterial loadMatFromFile(char * path)
{
	std::fstream File;

	std::string final_name;
	std::string final_collision;
	std::string final_speed;
	std::string final_texture;

	File.open(path, std::ios::in);

	char identifier[4];

	for (int i = 0; i != 3; ++i) {
		identifier[i] = File.get();
	}
	identifier[3] = '\0';

	if (strcmp(identifier, "mat")) {
		DebugUtilities::printErr("Kein gültiges Material...");
		return CMaterial();
	}
	while (!File.eof()) {
		char id = File.get();
		if (id == 'n') {
			File.seekp(-1, File.cur);
			std::string name;
			for (int i = 0; i != 5; ++i) {
				name.push_back(File.get());
			}
			if (!strcmp(name.c_str(), "name=")) {
				char* tmp = (char*)malloc(512);
				File.getline(tmp, 512);
				final_name = tmp;
				free(tmp);
			}
		}
		else if (id == 't') {
			File.seekp(-1, File.cur);
			std::string tex;
			for (int i = 0; i != 8; ++i) {
				tex.push_back(File.get());
			}
			if (!strcmp(tex.c_str(), "texture=")) {
				char* tmp = (char*)malloc(512);
				File.getline(tmp, 512);
				final_texture = tmp;
				free(tmp);
			}
		}
		else if (id == 'c') {
			File.seekp(-1, File.cur);
			std::string data;
			for (int i = 0; i != 10; ++i) {
				data.push_back(File.get());
			}
			if (!strcmp(data.c_str(), "collision=")) {
				char* tmp = (char*)malloc(512);
				File.getline(tmp, 512);
				final_collision = tmp;
				free(tmp);
			}
		}
		else if (id == 'w') {
			File.seekp(-1, File.cur);
			std::string data;
			for (int i = 0; i != 10; ++i) {
				data.push_back(File.get());
			}
			if (!strcmp(data.c_str(), "walkspeed=")) {
				char* tmp = (char*)malloc(512);
				File.getline(tmp, 512);
				final_speed = tmp;
				free(tmp);
			}
		}
	}

	bool bcollision;

	if (!strcmp(final_collision.c_str(), "false")) {
		bcollision = false;
	}
	else if (!strcmp(final_collision.c_str(), "true")) {
		bcollision = true;
	}

	float fwalkspeed = atof(final_speed.c_str());

	return CMaterial(final_name, g_pTextureManager->getTexture(final_texture), bcollision, fwalkspeed);
}
