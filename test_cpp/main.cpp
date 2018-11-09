// Deep Learning for Robust Normal Estimation in Unstructured Point Clouds
// Copyright (c) 2016 Alexande Boulch and Renaud Marlet
//
// This program is free software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation;
// either version 3 of the License, or any later version.
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
//
// PLEASE ACKNOWLEDGE THE AUTHORS AND PUBLICATION:
// "Deep Learning for Robust Normal Estimation in Unstructured Point Clouds "
// by Alexandre Boulch and Renaud Marlet, Symposium of Geometry Processing 2016,
// Computer Graphics Forum
//
// The full license can be retrieved at https://www.gnu.org/licenses/gpl-3.0.en.html

#include "Normals.h"

#include <boost/program_options.hpp>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <time.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv){
    srand (time(NULL));
    try{

        string input = "-1";
        string output = "out.xyz";
        int K = 100;
        int T = 1000;
        int n_phi=15;
        int n_rot=5;
        bool ua = false;
        float tol_angle_rad=0.79;
        int k_density = 5;
        string model = "";

        int c;

        opterr = 0;
        while ((c = getopt (argc, argv, "i:o:k:t:d:p:r:a:e:")) != -1)
        switch (c){
            case 'i':{
                input = optarg;
                break;
            }
            case 'o':{
                output = optarg;
                break;
            }
            case 'k':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> K;
                break;
            }
            case 't':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> T;
                break;
            }
            case 'd':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> ua;
                break;
            }
            case 'p':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> n_phi;
                break;
            }
            case 'r':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> n_rot;
                break;
            }
            case 'a':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> tol_angle_rad;
                break;
            }
            case 'e':{
                stringstream sstr("");
                sstr << optarg;
                sstr >> k_density;
                break;
            }
            default:{
                cout << "Unknown option character" << endl;
                return 1;
                break;
            }
            }

        if(input=="-1"){
            cout << "Error need input file" << endl;
            return 1;
        }

        // load the point cloud

        cout << "Create estimator" << endl;
        Eigen::MatrixX3d pc, normals;
        Eigen_Normal_Estimator ne(pc,normals);
        ne.loadXYZ(input);
        ne.set_K(K);
        ne.set_T(T);
        ne.set_density_sensitive(ua);
    	ne.set_n_phi(n_phi);
    	ne.set_n_rot(n_rot);
    	ne.set_tol_angle_rad(tol_angle_rad);
    	ne.set_K_density(k_density);

        cout << "Estimate" << endl;
        ne.estimate_normals();

        cout << "Save" << endl;
        // save the point cloud
        ne.saveXYZ(output);

    }catch(std::exception& e){
        std::cerr << "Unhandled Exception reached the top of main: "
                << e.what() << ", application will now exit " << std::endl;
        return 1;
    }
    return 0;
}
