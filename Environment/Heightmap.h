// Heightmap.h


class Heightmap {
	public:
		Heightmap(float, float, float);
		Heightmap(float, float, int**);
		Heightmap(float, float, float**);
		float getHeight(int, int);
		void getNormal(float, float, float*);
		bool isFloor(float, float);
		bool isWall(float, float);	

	private:
		void setHeight(int, int, float);
		void load(string);
		float** heightGrid;
}
