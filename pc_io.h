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

#ifndef PC_IO_HEADER
#define PC_IO_HEADER

#include<string>
#include"Eigen/Dense"
#include<vector>
#include<fstream>
#include<iostream>

void off_save(const std::string& filename, const Eigen::MatrixX3d& pc, const std::vector<std::vector<uint> >& faces=std::vector<std::vector<uint> >());

template<typename T>
void off_load(const std::string& filename, typename Eigen::Matrix<T, Eigen::Dynamic, 3>& pc, std::vector<std::vector<uint> >& faces){
	std::ifstream ifs(filename.c_str());

	if(!ifs.is_open()){
		std::cout << "OFF load: Error opening file" << std::endl;
		return;
	}

	std::string s_tmp;
	ifs >> s_tmp;

	if(s_tmp != "OFF"){
		std::cout << "OFF: format problem"<<std::endl;
		std::cout << s_tmp << std::endl;
		return;
	}

	int vertex_nbr;
	int faces_nbr;
	int edges_nbr;

	ifs >> vertex_nbr >> faces_nbr >> edges_nbr;

	pc.resize(vertex_nbr, 3);
	faces.resize(faces_nbr);
	for(int i=0; i<vertex_nbr; i++){
		ifs >> pc(i,0) >> pc(i,1) >> pc(i,2);
	}
	for(int i=0; i<faces_nbr; i++){
		int element_nbr;
		ifs >> element_nbr;
		faces[i].resize(element_nbr);
		for(int j=0; j<element_nbr; j++)
			ifs >> faces[i][j];
	}
}

void ply_load(const std::string& filename,
        Eigen::MatrixX3d& pc, Eigen::MatrixX3d& normals);

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::VectorXi& labels);

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::MatrixX3d& normals);

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc,const Eigen::MatrixX3i& colors);

void ply_save(const std::string& filename, const Eigen::MatrixX3d& pc, const Eigen::MatrixX3d& normals,const Eigen::MatrixX3i& colors);

#endif
