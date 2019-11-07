#include "pch.h"
#include "CSG_Constructor.h"
#include <igl/copyleft/cgal/mesh_boolean.h>

namespace csg {
	void objectToMatrices(Eigen::MatrixXf *V, Eigen::MatrixXi *F, Object::GeometricObject * object) {
		
		*F= Eigen::Map <Eigen::MatrixXi>(object->indices.data() , object->indices.size() /3, 3);
		/*for (size_t i = 0; i < object->vertices.size(); i = +3)
		{
			V->row(i) << object->vertices[i], object->vertices[i + 1], object->vertices[i + 2];
		}*/
		*V=Eigen::Map<Eigen::MatrixXf>(object->vertices.data(), object->vertices.size(), 3);
		/*for (size_t i = 0; i < object->indices.size(); i=+3)
		{
			F->row(i) << object->indices[i], object->indices[i+1], object->indices[i+2];
		}*/
	}
	void metriciesToObject(Eigen::MatrixXf *V, Eigen::MatrixXi *F, Object::GeometricObject * object) {
		/*object->indices.resize(F->size());
		object->vertices.resize(V->size());
		for (size_t i = 0; i < object->indices.size(); i++)
		{
			object->indices.push_back(F.);
		}*/

		object->indices = std::vector<int>(F->data(), F->data() + F->rows() * F->cols());
		object->indices = std::vector<int>(V->data(), V->data() + V->rows() * V->cols());


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