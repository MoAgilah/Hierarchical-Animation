#include "Hierarchy.h"
#include <algorithm>
#include <fstream>
#include <sstream> 

bool isUneeded(char c)
{
	return (c == '\"' || c == ',');
}

MeshComponent* Hiearchy::s_Root = nullptr;

Hiearchy::Hiearchy(std::string fN, std::string hfN, const XMFLOAT3& p, const XMFLOAT3& r, const double& s)
	:fName(fN),hfName(hfN), iP(p), iR(r), sF(s)
{
	Root = "";
}

Hiearchy::~Hiearchy()
{
	//delete s_Root;

	for (std::map<std::string, MeshComponent*>::iterator it = hierachie.begin(); it != hierachie.end(); it++)
	{
		delete it->second;
	}
}

MeshComponent* Hiearchy::GetByName(const std::string& name)
{
	return hierachie.find(name)->second;
}

MeshComponent* Hiearchy::GetRoot(void)
{
	return GetByName(Root);
}

std::map<std::string, MeshComponent*> Hiearchy::GetHierarchy(void)
{
	return hierachie;
}

void Hiearchy::LoadFromFile(void)
{
	std::string line;
	std::vector<std::string> l;
	float pX, pY, pZ;
	std::ifstream in;
	std::string path = "Resources/" + fName + "/" + hfName;
	in.open(path, std::fstream::out);

	while (getline(in, line)){
		line.erase(remove_if(line.begin(), line.end(), isUneeded), line.end());
		l.push_back(line);
	}

	in.close();

	Root = l[0];
	std::stringstream pos(l[2]);
	pos >> pX;	pos >> pY;	pos >> pZ;
	pX /= sF; pY /= sF; pZ /= sF;

	s_Root = new MeshComponent(XMFLOAT3(pX + iP.x, pY + iP.y, pZ + iP.z), XMFLOAT3(iR.x, iR.y, iR.z), fName, l[0]);
	hierachie.insert(std::pair<std::string, MeshComponent*>(l[0], s_Root));

	for (int i = 3; i < l.size(); i += 3)
	{
		std::stringstream pos(l[i + 2]);
		pos >> pX;	pos >> pY;	pos >> pZ;
		pX /= sF; pY /= sF; pZ /= sF;
		hierachie.insert(std::pair<std::string, MeshComponent*>(l[i], new MeshComponent(XMFLOAT3(pX, pY, pZ), XMFLOAT3(0, 0, 0), fName, l[i])));
	}

	for (int i = 3; i < l.size(); i += 3)
	{
		if (l[i + 1] != "")
		{
			GetByName(l[i + 1])->AddChild(GetByName(l[i]));
		}
	}
}

void Hiearchy::Draw(void)
{
	s_Root->Draw();
}

