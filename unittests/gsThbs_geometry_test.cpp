/*
Random tests with:
- random hierarchical subdomain configuration (generated by randomized box insertions to the Quadtree)
- uniform knot vectors with different multiplicities- multiplicity added by random. max multiplicity is equal to degree

Parameter to change for different test cases:
    T_nlevels - the maximum numbre of levels
    test_num - number of tests (different box configurations)
    point_num - number of evaluation points
    max_deg_x - the maximum degree in x-direction
    max_deg_y - the maximum degree in y-direction
    num_knots_x - maximum number of inner knots in x direction- the real value i generated by random
    num_knots_x - maximum number of inner knots in y direction- the real value i generated by random
    rand_knot_num - maximum number of inserted knots- increase the multiplicity of the knots- does not add new knot values
    max_level - maximum number of hierarchical levels
    box_num - maximum number of boxes inserted into one level of hierarchy
*/

#include "gismo_unittest.h"  // Brings in G+Smo and the UnitTest++ framework

using namespace gismo;


//lvl- max level of domain refinement, max number of boxes inserted
//per level, basis, alignement with the prewious level
std::vector<unsigned int> random_refinement(int lvl, int max_nb, 
                                            gismo::gsHTensorBasis<2> *bas, 
                                            bool aligned = false)
{

    //int max_x, max_y;
    int boxes_in_lvl, bi,span_size;
    std::vector<unsigned int> q;
    std::vector<gsVector<unsigned int> > boxes;// boxes stores the boxes inserted to the previous level
    std::vector<gsVector<unsigned int> > boxes_new;
    gsVector<unsigned int, 2> i1;
    gsVector<unsigned int, 2> i2;
    span_size = 1 << lvl;
    //std::cout<<"Spansize is :"<< span_size<<"\n";

    // left bottom corner box
    i1.setZero();
    i2[0] = bas->getBases()[0]->component(0).knots().unique().size()-1;
    i2[1] = bas->getBases()[0]->component(1).knots().unique().size()-1;

    i1[0] = i1[0] << (lvl); // get indices in lvl
    i1[1] = i1[1] << (lvl);
    i2[0] = i2[0] << (lvl);
    i2[1] = i2[1] << (lvl);

    boxes.push_back(i1);//insert the root of the tree into the boxes
    boxes.push_back(i2);
    srand((unsigned)time(NULL));//seed the random alg.
    for(int i = 0; i < lvl; i++){//insert lvl levels
        //std::cout<<"level: "<<i+1<< "\n";
        boxes_in_lvl = (rand()%max_nb);
        if(boxes_in_lvl == 0){
            boxes_in_lvl++;
        }
        for(int j = 0; j < boxes_in_lvl; j++){//insert number of boxes
            bi = rand() % (boxes.size()/2);//pick a box from prewious level
            if(aligned){
                //test if the box is a box not a point- insert only boxes
                i1[0] = ( ( (rand() % (boxes[2*bi+1][0]-boxes[2*bi][0]) ) + boxes[2*bi][0]) /span_size) << i;// left bottom corner box
                i1[1] = ( ( (rand() % (boxes[2*bi+1][1]-boxes[2*bi][1]) ) + boxes[2*bi][1]) /span_size) << i;
                i2[0] = ( ( (rand() % (boxes[2*bi+1][0]-i1[0]) +1) + i1[0]) /span_size) << i;// right top corner of the box
                i2[1] = ( ( (rand() % (boxes[2*bi+1][1]-i1[1]) +1) + i1[1]) /span_size) << i;

                i2[0] = math::max( i2[0], i1[0] + (bas->degree(1)+2)*(1 << lvl) );
                i2[1] = math::max( i2[1], i1[1] + (bas->degree(1)+2)*(1 << lvl) );
                
 
                //std::cout<<"\naligned box inserted ["<< i1[0]<<" , "<< i1[1]<<"] ["<< i2[0]<<" , "<< i2[1]<<"]"<< " to level "<<i+1 <<"\n";
                boxes_new.push_back(i1);
                boxes_new.push_back(i2);
                q.push_back(i+1);
                i1[0] = i1[0] >> (lvl - (i+1)); // get indices in level i+1
                i1[1] = i1[1] >> (lvl - (i+1));
                i2[0] = i2[0] >> (lvl - (i+1));
                i2[1] = i2[1] >> (lvl - (i+1));
                q.push_back(i1[0]);
                q.push_back(i1[1]);
                q.push_back(i2[0]);
                q.push_back(i2[1]);
                //bas->insert_box(i1,i2,i+1);
            }else{
                i1[0] = (rand() % (boxes[2*bi+1][0]-boxes[2*bi][0]) ) + boxes[2*bi][0];
                i1[1] = (rand() % (boxes[2*bi+1][1]-boxes[2*bi][1]) ) + boxes[2*bi][1];
                i2[0] = (rand() % (boxes[2*bi+1][0]-i1[0]) +1) + i1[0];
                i2[1] = (rand() % (boxes[2*bi+1][1]-i1[1]) +1) + i1[1];
                if( (i1[0]==i2[0]) || (i1[1]==i2[1]) ){
                    i2[0] += span_size;
                    i2[1] += span_size;
                }
                //std::cout<<"\nbox inserted ["<< i1[0]<<" , "<< i1[1]<<"] ["<< i2[0]<<" , "<< i2[1]<<"]"<< " to level "<<i+1 <<"\n";
                boxes_new.push_back(i1);
                boxes_new.push_back(i2);
                q.push_back(i+1);
                i1[0] = i1[0] >> (lvl - (i+1)); // get indices in level i+1
                i1[1] = i1[1] >> (lvl - (i+1));
                i2[0] = i2[0] >> (lvl - (i+1));
                i2[1] = i2[1] >> (lvl - (i+1));
                q.push_back(i1[0]);
                q.push_back(i1[1]);
                q.push_back(i2[0]);
                q.push_back(i2[1]);
                //bas->insert_box(i1,i2,i+1);
            }
        }
        span_size = span_size/2;
        //cout<<"Spansize is :"<< span_size<<endl;
        boxes.clear();
        for(unsigned int k = 0; k < boxes_new.size();k++){
            boxes.push_back(boxes_new[k]);
        }
        boxes_new.clear();
    }
    return q;
}


TEST(gsThbs_geometry_test)
{
  gsVector<unsigned int> iv1;
  gsVector<unsigned int> iv2;
  iv1.resize(2);
  iv2.resize(2);

  ////////THB spline tests///////////////////////


    //gsInfo << " ----- Test THBSplineBasis ----------  \n";
    //gsInfo << " Uniform knots with different multiplicities and d+1 multiplicity at the boundary.\n";
    srand((unsigned)time(NULL));//seed the random alg.
    int test_num = 1;
    int point_num = 10;
    int max_deg_x = 2;
    int max_deg_y = 2;
    int num_knots_x = 2;
    int num_knots_y = 2;
    int rand_knot_num = 0;
    int max_level = 2;
    int box_num = 5;
    // gsInfo << " Number of tests: "<< test_num <<"\n";
    // gsInfo << " Number of points: "<< point_num <<"\n";
    for(int i =0; i < test_num;i++){
        //gsInfo << " ------------------------------------------------------------------------------ test number "<<i<<" \n";
        int deg_x = (rand()%max_deg_x)+1;
        int deg_y = (rand()%max_deg_y)+1;
        int kn = (rand()%num_knots_x)+1;
        gsKnotVector<> T_KV (0, 1, kn , deg_x+1, 1 ) ;
        kn = (rand()%num_knots_y)+1;
        gsKnotVector<> T_KV1 (0, 1,kn,deg_y+1,1) ;
        //gsInfo<<"Knot Vector"<<T_KV<<"\n";
        //gsInfo<<"Knot Vector"<<T_KV1<<"\n";
        for (int i2 = 0; i2 < rand_knot_num; i2 ++){
            int kn2 = rand()%T_KV.size();
            if(T_KV.multiplicity(T_KV[kn2]) < deg_x ){
                T_KV.insert(T_KV[kn2]);
            }
        }
        for (int i3 = 0; i3 < rand_knot_num; i3 ++){
            int kn3 = rand()%T_KV1.size();
            if(T_KV1.multiplicity(T_KV1[kn3]) < deg_y ){
                T_KV1.insert(T_KV1[kn3]);
            }
        }
        //gsInfo<<"Knot Vector"<<T_KV<<"\n";
        //gsInfo<<"Knot Vector"<<T_KV1<<"\n";
        gsTensorBSplineBasis<2> T_tbasis( T_KV, T_KV1 );

        int T_nlevels =(rand()%max_level)+2;
        gsTHBSplineBasis<2>  TT ( T_tbasis ) ;//necessary to create the refinement
        gsTHBSplineBasis<2>  THB ( T_tbasis , random_refinement(T_nlevels-1, box_num, &TT )) ;

        //gsInfo<<"knot vector"<< THB.m_cvs[0][0]<<"\n";
        //gsInfo<<"knot vector"<< THB.m_cvs[1][0]<<"\n";
        //gsInfo<<"Basis has degree "<< deg_x <<" and "<< deg_y <<". The number of levels is "<< T_nlevels<<"\n";

        //gsInfo<<"The tree has "<< THB.tree().size() << " nodes.\n" << "\n";

        // THB.printCharMatrix();

        gsMatrix<> T_para  = THB.support();
        gsVector<> T_c0 = T_para.col(0);
        gsVector<> T_c1 = T_para.col(1);
        gsMatrix<> T_pts = uniformPointGrid(T_c0,T_c1, point_num) ;

        //gsInfo<<"\n"<< "The parameter range is: "<< "\n" << T_para <<"\n";
        ////////coefficient matrix creation///////////
        gsMatrix<> anch = THB.anchors();

        //gsInfo<<"anchors"<< anch<<"\n";
        gsMatrix<> eye = gsMatrix<>::Identity(THB.size(), THB.size());
        gsTHBSpline<2> THB_geometry ( THB, eye);
        gsMatrix<>   T_ev_geom  = THB_geometry.eval(anch);
        gsMatrix<>   T_ev  = THB.eval(anch) ;
        //gsInfo<<"eval  geometry \n"<<  T_ev_geom <<"\n";
        CHECK_MATRIX_PARTITION_OF_UNIT_CLOSE(T_ev, (real_t)0.0000001);
    }

}

