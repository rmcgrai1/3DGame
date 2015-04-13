#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/Texture.h"
#include "Pos3D.h"
#include "Face.h"
#include "Mtl.h"

using namespace std;
class Model {
	friend ostream& operator<<(ostream&, const Model);
	public:
		Model(string Location = "Resources/Models/default", TexturePack *TP = new TexturePack); // defaults to loading "model.obj" in the specified folder
		Model(string Location, string filename, TexturePack *TP); // real constructor that uses specified file in the folder
		Pos3D **getVertices();
		Pos3D **getTexCoords();
		Pos3D **getVNormals();
		Face **getFaces();
		int getVertexCount();
		int getTexCoordCount();
		int getVNormalCount();
		int getFaceCount();
	private:
		void Initialize(string Location, string filename, TexturePack *TP);
		void UpdateLists();
		
		TexturePack *Textures;
		string directory;
		string subfile;
		vector<Pos3D *> *AllVertices;
		Pos3D ** Vertices;
		int VertexCount;
		vector<Pos3D *> *AllTexCoords;
		Pos3D ** TexCoords;
		int TexCoordCount;
		vector<Pos3D *> *AllVNormals;
		Pos3D ** VNormals;
		int VNormalCount;
		vector<Face *> *AllFaces;
		Face ** Faces;
		int FaceCount;
		
		map<string, Mtl *> Materials;
};

#endif