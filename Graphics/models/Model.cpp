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

#include "Model.h"

/*Pos3D **Model::Vertices;
Pos3D **Model::TexCoords;
Pos3D **Model::VNormals;
Face **Model::Faces;
int Model::VertexCount;
int Model::TexCoordCount;
int Model::VNormalCount;
int Model::FaceCount;*/

using namespace std;
Model::Model(string Location, TexturePack *TP) { // defaults to loading "model.obj" in the specified folder
	Initialize(Location, "model.obj", TP);
}

Model::Model(string Location, string filename, TexturePack *TP) {
	Initialize(Location, filename, TP);
}

void Model::Initialize(string Location, string filename, TexturePack *TP) {
	Textures = TP;
	directory = Location;
	subfile = filename;
	Vertices = NULL; // for now set to NULL until first call of UpdateLists()
	TexCoords = NULL; // for now set to NULL until first call of UpdateLists()
	VNormals = NULL; // for now set to NULL until first call of UpdateLists()
	Faces = NULL; // for now set to NULL until first call of UpdateLists()
	AllVertices = new vector<Pos3D *>;
	AllTexCoords = new vector<Pos3D *>;
	AllVNormals = new vector<Pos3D *>;
	AllFaces = new vector<Face *>;
	string TexturePackFolder = Textures->GetFolder();
	Mtl *CurrentMaterial = NULL;
	
	string ModelFileName = TexturePackFolder + "/" + directory + "/" + subfile;
	ifstream ModelFile;
	ModelFile.open(ModelFileName.c_str());
	if(ModelFile.is_open()) {
		while(!ModelFile.eof()) {
			char ThisLineCstr[256];
			ModelFile.get(ThisLineCstr, 256, '\r'); // only works with windows EOLs - probably will read in 256 chars as 1 line if unix EOLs used
			string ThisLine(ThisLineCstr);
			ModelFile.ignore(1,'\n');
			if(ThisLine.at(0)!='#') {
				int pos = ThisLine.find(" ");
				string Command = ThisLine.substr(0,pos);
				string Params = ThisLine.substr(pos+1,256);
				if(Command=="v") {
					AllVertices->push_back(new Pos3D(Params));
				} else if(Command=="vt") {
					AllTexCoords->push_back(new Pos3D(Params));
				} else if(Command=="vn") {
					AllVNormals->push_back(new Pos3D(Params));
				} else if(Command=="f") {
					AllFaces->push_back(new Face(Params, CurrentMaterial));
				} else if(Command=="usemtl") {
					CurrentMaterial = Materials[Params];
				} else if(Command=="mtllib") {
					Mtl *ThisMaterial = NULL;
					ifstream MtlFile;
					MtlFile.open(Params.c_str());
					if(MtlFile.is_open()) {
						while(!MtlFile.eof()) {
							char ThisMtlLineCstr[256];
							MtlFile.get(ThisMtlLineCstr, 256, '\r'); // only works with windows EOLs - probably will read in 256 chars as 1 line if unix EOLs used
							string ThisMtlLine(ThisMtlLineCstr);
							MtlFile.ignore(1,'\n');
							if(ThisMtlLine.at(0)!='#') {
								if(ThisMtlLine.substr(0,6)=="newmtl") {
									string ThisMtlName = ThisLine.substr(7,256);
									ThisMaterial = new Mtl(directory,Textures);
									Materials[ThisMtlName] = ThisMaterial;
								} else if(ThisMaterial) {
									ThisMaterial->InterpretLine(ThisMtlLine);
								} else {
									cout << "Unrecognized command in mtl file!!!\n";
								}
							}
						}
					} else {
						cout << "Could not open mtl file! switching to default texture!\n";
						ThisMaterial = new Mtl(directory,Textures);
						Materials["__Metal_Brass_Ceiling__Metal_Brass_Ceiling_jpg"] = ThisMaterial;
						ThisMaterial->InterpretLine("map_Kd Metal_Brass_Ceiling.jpg");
					}
				} else {
					cout << "Unrecognized command \"" << Command << "\" in obj file!!! Ignoring line!!!\n";
				}
			}
		}
		ModelFile.close();
	} else {
		cout << "File \"" << ModelFileName << "\"not loaded! Loading default shape!\n";
		//load dummy triangular prism into model instead of from file
		//loading dummy points into model
		AllVertices->push_back(new Pos3D(0,0,0));
		AllVertices->push_back(new Pos3D(1,0,0));
		AllVertices->push_back(new Pos3D(1,0,1));
		AllVertices->push_back(new Pos3D(0,1,0));
		AllVertices->push_back(new Pos3D(1,1,0));
		AllVertices->push_back(new Pos3D(1,1,1));
		//loading dummy texture coordinates into model
		AllTexCoords->push_back(new Pos3D(0,0,0));
		AllTexCoords->push_back(new Pos3D(0,1,0));
		AllTexCoords->push_back(new Pos3D(1,0,0));
		AllTexCoords->push_back(new Pos3D(1,1,0));
		//loading dummy vertex normals into model
		AllVNormals->push_back(new Pos3D(0,0,0));
		AllVNormals->push_back(new Pos3D(0,1,0));
		AllVNormals->push_back(new Pos3D(1,0,0));
		AllVNormals->push_back(new Pos3D(1,1,0));
		AllVNormals->push_back(new Pos3D(1,0,0));
		AllVNormals->push_back(new Pos3D(1,1,0));
		//loading dummy materials into model
		Mtl *ThisMaterial = new Mtl(directory,Textures);
		ThisMaterial->InterpretLine("map_Kd Metal_Brass_Ceiling.jpg");
		Materials["__Metal_Brass_Ceiling__Metal_Brass_Ceiling_jpg"] = ThisMaterial;
		//loading dummy faces into model
		AllFaces->push_back(new Face(1,1,1, 2,3,2, 3,4,3, ThisMaterial));
		AllFaces->push_back(new Face(1,1,1, 3,3,3, 6,4,6, ThisMaterial));
		AllFaces->push_back(new Face(1,1,1, 6,4,6, 4,2,4, ThisMaterial));
		AllFaces->push_back(new Face(4,3,4, 6,2,6, 5,1,5, ThisMaterial));
		AllFaces->push_back(new Face(4,1,4, 5,3,5, 1,2,1, ThisMaterial));
		AllFaces->push_back(new Face(2,4,2, 1,2,1, 5,3,5, ThisMaterial));
		AllFaces->push_back(new Face(2,1,2, 5,3,5, 3,2,3, ThisMaterial));
		AllFaces->push_back(new Face(3,2,3, 5,3,5, 6,4,6, ThisMaterial));
	}
	
	
	
	UpdateLists();
}

Pos3D **Model::getVertices() {
	return Vertices;
}

Pos3D **Model::getTexCoords() {
	return TexCoords;
}

Pos3D **Model::getVNormals() {
	return VNormals;
}

Face **Model::getFaces() {
	return Faces;
}

int Model::getVertexCount() {
	return VertexCount;
}

int Model::getTexCoordCount() {
	return TexCoordCount;
}

int Model::getVNormalCount() {
	return VNormalCount;
}

int Model::getFaceCount() {
	return FaceCount;
}


void Model::UpdateLists() {
	vector<Pos3D *>::iterator i;
	vector<Face *>::iterator i2;
	int j;
	// Update Vertices from AllVertices
	j=0;
	if(Vertices) { // make sure isn't NULL
		delete[] Vertices; // remove list of vertices
	}
	VertexCount = AllVertices->size();
	Vertices = new Pos3D* [VertexCount];
	for(i=AllVertices->begin();i!=AllVertices->end();i++) {
		if(j<VertexCount && j>=0) { // make sure j is in bounds - should always be true, but is here for safety
			Vertices[j] = *i;
		}
		j++;
	}
	// Update TexCoords from AllTexCoords
	j=0;
	if(TexCoords) { // make sure isn't NULL
		delete[] TexCoords; // remove list of TexCoords
	}
	TexCoordCount = AllTexCoords->size();
	TexCoords = new Pos3D* [TexCoordCount];
	for(i=AllTexCoords->begin();i!=AllTexCoords->end();i++) {
		if(j<TexCoordCount && j>=0) { // make sure j is in bounds - should always be true, but is here for safety
			TexCoords[j] = *i;
		}
		j++;
	}
	// Update VNormals from AllVNormals
	j=0;
	if(VNormals) { // make sure isn't NULL
		delete[] VNormals; // remove list of VNormals
	}
	VNormalCount = AllVNormals->size();
	VNormals = new Pos3D* [VNormalCount];
	for(i=AllVNormals->begin();i!=AllVNormals->end();i++) {
		if(j<VNormalCount && j>=0) { // make sure j is in bounds - should always be true, but is here for safety
			VNormals[j] = *i;
		}
		j++;
	}
	// Update Faces from AllFaces
	j=0;
	if(Faces) { // make sure isn't NULL
		delete[] Faces; // remove list of Faces
	}
	FaceCount = AllFaces->size();
	Faces = new Face* [FaceCount];
	for(i2=AllFaces->begin();i2!=AllFaces->end();i2++) {
		if(j<FaceCount && j>=0) { // make sure j is in bounds - should always be true, but is here for safety
			Faces[j] = *i2;
		}
		j++;
	}
}

ostream& operator<<(ostream& output, const Model model) {
	output << model.directory << "/" << model.subfile;
	return output;
}