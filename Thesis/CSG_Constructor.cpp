#include "pch.h"

#include "CSG_Constructor.h"
#ifndef _WITHOUT_LIBIGL
//#pragma warning(push ,0)
#include <igl/copyleft/cgal/mesh_boolean.h>
//#pragma warning(pop)
#include "CalculateMeshNormals.h"

namespace csg {
	void objectToMatrices(Eigen::MatrixXf *V, Eigen::MatrixXi *F, Object::GeometricObject * object) {
		if (object->verticesR.size()!=0)
		{
			*F = Eigen::MatrixXi(object->indicesR.size() / 3, 3);


			for (size_t i = 0; i < object->indicesR.size() / 3; i++)
			{
				F->row(i) << object->indicesR[i * 3], object->indicesR[i * 3 + 1], object->indicesR[i * 3 + 2];
			}
			*V = Eigen::MatrixXf(object->verticesR.size() / 3, 3);
			for (size_t i = 0; i < object->verticesR.size() / 3; i++)
			{
				V->row(i) << object->verticesR[i * 3], object->verticesR[i * 3 + 1], object->verticesR[i * 3 + 2];
			}
		}
		else {

			*F = Eigen::MatrixXi(object->indices.size() / 3, 3);


			for (size_t i = 0; i < object->indices.size() / 3; i++)
			{
				F->row(i) << object->indices[i * 3], object->indices[i * 3 + 1], object->indices[i * 3 + 2];
			}
			*V = Eigen::MatrixXf(object->vertices.size() / 3, 3);
			for (size_t i = 0; i < object->vertices.size() / 3; i++)
			{
				V->row(i) << object->vertices[i * 3], object->vertices[i * 3 + 1], object->vertices[i * 3 + 2];
			}
		}
		

	}
	void metriciesToObject(Eigen::MatrixXf *V, Eigen::MatrixXi *F, Object::GeometricObject * object) {

		F->transposeInPlace();
		V->transposeInPlace();

		object->indicesR = std::vector<int>(F->data(), F->data() + F->rows() * F->cols());
		object->verticesR = std::vector<float>(V->data(), V->data() + V->rows() * V->cols());
		CalculateMeshNormals::calculateNormals(&object->indicesR,&object->verticesR, &object->indices, &object->vertices, &object->normals);

	}
	void computeCSG(Object::GeometricObject * objectA, Object::GeometricObject * objectB, igl::MeshBooleanType booleanType, Object::GeometricObject * objectOUT) {
		Eigen::MatrixXf V1;
		Eigen::MatrixXi F1;
		objectToMatrices(&V1, &F1, objectA);
		Eigen::MatrixXf V2;
		Eigen::MatrixXi F2;
		objectToMatrices(&V2, &F2, objectB);
		Eigen::MatrixXf Vout;
		Eigen::MatrixXi Fout;
		igl::copyleft::cgal::mesh_boolean(V1, F1, V2, F2, booleanType, Vout, Fout); 
		metriciesToObject(&Vout,&Fout, objectOUT);
	}
	void CSG_union(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB) {
		computeCSG(objectA, objectB, igl::MESH_BOOLEAN_TYPE_UNION, objectOUT);
	}
	void CSG_intersection(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB) {
		computeCSG(objectA, objectB, igl::MESH_BOOLEAN_TYPE_INTERSECT, objectOUT);
	}
	void CSG_minus(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB){
		computeCSG(objectA, objectB, igl::MESH_BOOLEAN_TYPE_MINUS, objectOUT);
	}
	void CSG_XOR(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB) {
		computeCSG(objectA, objectB, igl::MESH_BOOLEAN_TYPE_XOR, objectOUT);
	}
}

#else //WITHOUT_LIBIGL
namespace csg {
#ifndef NO_CSG_WARNING
#pragma message("CSG oparations doesn't work without libigl library. Define NO_CSG_WARNING to hide this warning.")
#endif
	void CSG_union(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB) {}
	void CSG_intersection(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB) {}
	void CSG_minus(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB){}
	void CSG_XOR(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB){}
}
#endif //WITHOUT_LIBIGL
