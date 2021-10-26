#include "modelmanager.h"
#define TINYOBJLOADER_IMPLEMENTATION 
#include "dependencies/tiny_obj_loader.h"
#include <iostream>
#include <cassert>
#include "common/workdirs.h"

bool loadObj(const char* modelPath, const char* matPath, tinyobj::attrib_t& attr, std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& materials)
{
    tinyobj::ObjReaderConfig reader_config;

    reader_config.mtl_search_path = matPath; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(modelPath, reader_config)) 
    {
        if (!reader.Error().empty()) 
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return false;
    }

    if (!reader.Warning().empty()) 
    {
        std::cout << "TinyObjReader: " << reader.Warning();
        return false;
    }

    attr            = reader.GetAttrib();
    shapes          = reader.GetShapes();
    materials       = reader.GetMaterials();
    printf("Found: %s\n",modelPath);
    return true;
}

// Returns true iif v1 can be considered equal to v2
bool is_near(float v1, float v2){
	return fabs( v1-v2 ) < 0.01f;
}

// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool getSimilarVertexIndex( 
	glm::vec3 & in_vertex, 
	glm::vec2 & in_uv, 
	glm::vec3 & in_normal, 
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	unsigned int & result
){
	// Lame linear search
	for ( unsigned int i=0; i<out_vertices.size(); i++ ){
		if (
			is_near( in_vertex.x , out_vertices[i].x ) &&
			is_near( in_vertex.y , out_vertices[i].y ) &&
			is_near( in_vertex.z , out_vertices[i].z ) &&
			is_near( in_uv.x     , out_uvs     [i].x ) &&
			is_near( in_uv.y     , out_uvs     [i].y ) &&
			is_near( in_normal.x , out_normals [i].x ) &&
			is_near( in_normal.y , out_normals [i].y ) &&
			is_near( in_normal.z , out_normals [i].z )
		){
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}

void indexVBO_slow(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned int> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);

		if ( found ){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back( in_vertices[i]);
			out_uvs     .push_back( in_uvs[i]);
			out_normals .push_back( in_normals[i]);
			out_indices .push_back( (unsigned int)out_vertices.size() - 1 );
		}
	}
}

struct PackedVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

bool getSimilarVertexIndex_fast( PackedVertex & packed, std::map<PackedVertex,unsigned int> & VertexToOutIndex, unsigned int & result)
{
	std::map<PackedVertex,unsigned int>::iterator it = VertexToOutIndex.find(packed);
	if ( it == VertexToOutIndex.end() ){
		return false;
	}else{
		result = it->second;
		return true;
	}
}

void indexVBO(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned int> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	std::map<PackedVertex,unsigned int> VertexToOutIndex;

	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};
		

		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = getSimilarVertexIndex_fast( packed, VertexToOutIndex, index);

		if ( found ){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back( in_vertices[i]);
			out_uvs     .push_back( in_uvs[i]);
			out_normals .push_back( in_normals[i]);
			unsigned int newindex = (unsigned int)out_vertices.size() - 1;
			out_indices .push_back( newindex );
			VertexToOutIndex[ packed ] = newindex;
		}
	}
}







void indexVBO_TBN(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,
	std::vector<glm::vec3> & in_tangents,
	std::vector<glm::vec3> & in_bitangents,

	std::vector<unsigned int> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec3> & out_tangents,
	std::vector<glm::vec3> & out_bitangents
){
	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		// Try to find a similar vertex in out_XXXX
		unsigned int index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);

		if ( found ){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );

			// Average the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back( in_vertices[i]);
			out_uvs     .push_back( in_uvs[i]);
			out_normals .push_back( in_normals[i]);
			out_tangents .push_back( in_tangents[i]);
			out_bitangents .push_back( in_bitangents[i]);
			out_indices .push_back( (unsigned int)out_vertices.size() - 1 );
		}
	}
}


bool
modelmanager::LoadObj(const char* path, const char* matPath, Model* model)
{
    tinyobj::attrib_t                   attrib;
    std::vector<tinyobj::shape_t>       shapes;
    std::vector<tinyobj::material_t>    materials;
	std::string usrPath 		= path;
	std::string materialPath 	= matPath;
    if(!loadObj((workdirs::assetDir + usrPath).c_str(), (workdirs::assetDir + materialPath).c_str(), attrib, shapes, materials)) return false;


    for (size_t s = 0; s < shapes.size(); s++) 
    {   
        printf("Fetching information from: %s \n", shapes[s].name.c_str());

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> colors;

        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            for (size_t v = 0; v < fv; v++) 
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                glm::vec3 pos;

                pos.x = attrib.vertices[3*size_t(idx.vertex_index)+0];
                pos.y = attrib.vertices[3*size_t(idx.vertex_index)+1];
                pos.z = attrib.vertices[3*size_t(idx.vertex_index)+2];

                positions.push_back(pos);

                if (idx.normal_index >= 0) 
                {
                    glm::vec3 nor;
                    nor.x = attrib.normals[3*size_t(idx.normal_index)+0];
                    nor.y = attrib.normals[3*size_t(idx.normal_index)+1];
                    nor.z = attrib.normals[3*size_t(idx.normal_index)+2];
                    normals.push_back(nor);
                }

                if (idx.texcoord_index >= 0) 
                {
                    glm::vec2 uv;
                    uv.x           = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    uv.y           = attrib.texcoords[2*size_t(idx.texcoord_index)+1]; 
                    uvs.push_back(uv);            
                }

                glm::vec3 col;
                col.x = attrib.colors[3*size_t(idx.vertex_index)+0];
                col.y = attrib.colors[3*size_t(idx.vertex_index)+1];
                col.z = attrib.colors[3*size_t(idx.vertex_index)+2];
                colors.push_back(col);
                

            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }


        Mesh mesh;
        
        std::vector<glm::vec3>      outPositions;
        std::vector<glm::vec3>      outNormals;
        std::vector<glm::vec2>      outUvs;
        std::vector<unsigned int >  outIndices;
        std::vector<glm::vec3>      outColors;

        indexVBO(positions,uvs,normals,mesh.indices, mesh.positions, mesh.uvs, mesh.normals );
		
        model->meshes.push_back(mesh);
    }

    return true;

}