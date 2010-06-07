#include <MudUtils.h>

namespace Mud {

    void Utils::GetMeshInformation(
        const Ogre::MeshPtr mesh,
        size_t &vertex_count,
        Ogre::Vector3* &vertices,
        size_t &index_count,
        unsigned* &indices)
    {
        bool added_shared = false;
        size_t current_offset = 0;
        size_t shared_offset = 0;
        size_t next_offset = 0;
        size_t index_offset = 0;


        vertex_count = index_count = 0;

        for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
        {
            Ogre::SubMesh* submesh = mesh->getSubMesh(i);
            if(submesh->useSharedVertices)
            {
                if( !added_shared )
                {
                    vertex_count += mesh->sharedVertexData->vertexCount;
                    added_shared = true;
                }
            }
            else
            {
                vertex_count += submesh->vertexData->vertexCount;
            }
            index_count += submesh->indexData->indexCount;
        }


        vertices = new Ogre::Vector3[vertex_count];
        indices = new unsigned[index_count];

        added_shared = false;

        for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
        {
            Ogre::SubMesh* submesh = mesh->getSubMesh(i);

            Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

            if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
            {
                if(submesh->useSharedVertices)
                {
                    added_shared = true;
                    shared_offset = current_offset;
                }

                const Ogre::VertexElement* posElem =
                    vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

                Ogre::HardwareVertexBufferSharedPtr vbuf =
                    vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

                unsigned char* vertex =
                    static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

                float* pReal;

                for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
                {
                    posElem->baseVertexPointerToElement(vertex, &pReal);
                    Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
                    vertices[current_offset + j] = pt;
                }
                
                vbuf->unlock();
                next_offset += vertex_data->vertexCount;
            }


            Ogre::IndexData* index_data = submesh->indexData;
            size_t numTris = index_data->indexCount / 3;
            Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
            
            bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

            unsigned long* pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

            size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;

            if ( use32bitindexes )
            {
                for ( size_t k = 0; k < numTris*3; ++k)
                {
                    indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
                }
            }
            else
            {
                for ( size_t k = 0; k < numTris*3; ++k)
                {
                    indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
                                              static_cast<unsigned long>(offset);
                }
            }

            ibuf->unlock();
            current_offset = next_offset;
        }
    }


}

