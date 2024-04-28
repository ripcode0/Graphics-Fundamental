#pragma once

#include <string>
#include <algorithm>
#include <vector>

struct vertex_index_t
{
    int v,vt,vn;
    vertex_index_t() : v(-1), vt(-1), vn(-1) {}
    vertex_index_t(int v_index, int vt_index, int vn_index) 
        : v(v_index), vt(vt_index), vn(vn_index) {}
};

struct face_t
{
    std::vector<vertex_index_t> indices;
    unsigned int smoothing_group_id;
    int pad;
    face_t() : smoothing_group_id(0), pad(0) {}    
};

