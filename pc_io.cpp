/* License Information
 *
 *  Copyright (C) ONERA, The French Aerospace Lab
 *  Author: Alexandre BOULCH
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this
 *  software and associated documentation files (the "Software"), to deal in the Software
 *  without restriction, including without limitation the rights to use, copy, modify, merge,
 *  publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 *  to whom the Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *  OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 *  Note that this library relies on external libraries subject to their own license.
 *  To use this software, you are subject to the dependencies license, these licenses
 *  applies to the dependency ONLY  and NOT this code.
 *  Please refer below to the web sites for license informations:
 *       PCL, BOOST,NANOFLANN, EIGEN, LUA TORCH
 *
 * When using the software please aknowledge the  corresponding publication:
 * "Deep Learning for Robust Normal Estimation in Unstructured Point Clouds "
 * by Alexandre Boulch and Renaud Marlet
 * Symposium of Geometry Processing 2016, Computer Graphics Forum
 */

#include "pc_io.h"

#include<fstream>
#include<iostream>

using namespace std;

void off_save(const std::string& filename, const Eigen::MatrixX3d& pc, const std::vector<std::vector<uint> >& faces){
	std::ofstream ofs(filename.c_str());

	if(!ofs.is_open()){
		cout << "OFF SAVE: Error opening file" << endl;
		return;
	}

	ofs << "OFF" << endl;
	ofs << pc.rows() << " " << faces.size() << " 0" <<endl;
	for(uint i=0; i<pc.rows(); i++){
		ofs << pc.row(i)[0] << " ";
		ofs << pc.row(i)[1] << " ";
		ofs << pc.row(i)[2];
		ofs<< endl;
	}
	for(uint i=0; i<faces.size(); i++){
		ofs << faces[i].size();
		for(uint j=0; j<faces[i].size(); j++)
			ofs << " " << faces[i][j];
		ofs << endl;
	}
	ofs.close();
}


#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl/io/ply_io.h>

void ply_load(const std::string& filename,
        Eigen::MatrixX3d& pc, Eigen::MatrixX3d& normals){

		pcl::PointCloud<pcl::PointNormal>::Ptr pcl_cloud(new pcl::PointCloud<pcl::PointNormal>);
		pcl::io::loadPLYFile(filename, *pcl_cloud);

		pc.resize(pcl_cloud->size(), 3);
		normals.resize(pcl_cloud->size(),3);
		for(int i=0; i<pcl_cloud->size(); i++){
			pc(i,0) = pcl_cloud->points[i].x;
			pc(i,1) = pcl_cloud->points[i].y;
			pc(i,2) = pcl_cloud->points[i].z;
			normals(i,0) = pcl_cloud->points[i].normal_x;
			normals(i,1) = pcl_cloud->points[i].normal_y;
			normals(i,2) = pcl_cloud->points[i].normal_z;
		}
}

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::VectorXi& labels){


	int n_labels = labels.maxCoeff()+1;
	Eigen::MatrixX3i colors(n_labels,3);
	for(int i=0; i<n_labels; i++){
		colors.row(i) = Eigen::Vector3i(rand()%256, rand()%256, rand()%256);
	}

	std::ofstream ofs(filename.c_str());
	if(!ofs.is_open()){
		cout << "PLY SAVE: Error opening file" << endl;
		return;
	}

	ofs << "ply" << endl;
	ofs << "format ascii 1.0" << endl;

	ofs << "element vertex " << pc.rows() << endl;
	ofs << "property float x"<< endl;
	ofs << "property float y"<< endl;
	ofs << "property float z"<< endl;
	ofs << "property uchar red"<< endl;  // le rouge du code RGB
	ofs << "property uchar green"<< endl;  // le vert
	ofs << "property uchar blue"<< endl;  // le bleu
	ofs << "end_header" << endl;

	for(uint i=0; i<pc.rows(); i++){
		ofs << pc.row(i)[0] << " ";
		ofs << pc.row(i)[1] << " ";
		ofs << pc.row(i)[2] << " ";
		ofs << colors(labels(i),0) << " ";
		ofs << colors(labels(i),1) << " ";
		ofs << colors(labels(i),2) ;
		ofs << endl;
	}
	ofs.close();
}

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::MatrixX3d& normals){



	std::ofstream ofs(filename.c_str());
	if(!ofs.is_open()){
		cout << "PLY SAVE: Error opening file" << endl;
		return;
	}

	ofs << "ply" << endl;
	ofs << "format ascii 1.0" << endl;

	ofs << "element vertex " << pc.rows() << endl;
	ofs << "property float x"<< endl;
	ofs << "property float y"<< endl;
	ofs << "property float z"<< endl;
	ofs << "property float nx"<< endl;
	ofs << "property float ny"<< endl;
	ofs << "property float nz"<< endl;
	ofs << "end_header" << endl;

	for(uint i=0; i<pc.rows(); i++){
		ofs << pc.row(i)[0] << " ";
		ofs << pc.row(i)[1] << " ";
		ofs << pc.row(i)[2] << " ";
		ofs << normals(i,0) << " ";
		ofs << normals(i,1) << " ";
		ofs << normals(i,2) ;
		ofs << endl;
	}
	ofs.close();
}

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::MatrixX3i& colors){

	std::ofstream ofs(filename.c_str());
	if(!ofs.is_open()){
		cout << "PLY SAVE: Error opening file" << endl;
		return;
	}

	ofs << "ply" << endl;
	ofs << "format ascii 1.0" << endl;

	ofs << "element vertex " << pc.rows() << endl;
	ofs << "property float x"<< endl;
	ofs << "property float y"<< endl;
	ofs << "property float z"<< endl;
	ofs << "property uchar red"<< endl;  // le rouge du code RGB
	ofs << "property uchar green"<< endl;  // le vert
	ofs << "property uchar blue"<< endl;  // le bleu
	ofs << "end_header" << endl;

	for(uint i=0; i<pc.rows(); i++){
		ofs << pc(i,0) << " ";
		ofs << pc(i,1) << " ";
		ofs << pc(i,2) << " ";
		ofs << colors(i,0) << " ";
		ofs << colors(i,1) << " ";
		ofs << colors(i,2) ;
		ofs << endl;
	}
	ofs.close();
}

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc, const Eigen::MatrixX3d& normals,const Eigen::MatrixX3i& colors){

	std::ofstream ofs(filename.c_str());
	if(!ofs.is_open()){
		cout << "PLY SAVE: Error opening file" << endl;
		return;
	}

	ofs << "ply" << endl;
	ofs << "format ascii 1.0" << endl;

	ofs << "element vertex " << pc.rows() << endl;
	ofs << "property float x"<< endl;
	ofs << "property float y"<< endl;
	ofs << "property float z"<< endl;
	ofs << "property float nx"<< endl;
	ofs << "property float ny"<< endl;
	ofs << "property float nz"<< endl;
	ofs << "property uchar red"<< endl;  // le rouge du code RGB
	ofs << "property uchar green"<< endl;  // le vert
	ofs << "property uchar blue"<< endl;  // le bleu
	ofs << "end_header" << endl;

	for(uint i=0; i<pc.rows(); i++){
		ofs << pc(i,0) << " ";
		ofs << pc(i,1) << " ";
		ofs << pc(i,2) << " ";
		ofs << normals(i,0) << " ";
		ofs << normals(i,1) << " ";
		ofs << normals(i,2) << " ";
		ofs << colors(i,0) << " ";
		ofs << colors(i,1) << " ";
		ofs << colors(i,2) ;
		ofs << endl;
	}
	ofs.close();
}
