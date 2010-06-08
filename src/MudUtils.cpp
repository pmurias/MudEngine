#include <MudUtils.h>

namespace Mud {

    void Utils::GetMeshInformation(
        const Ogre::MeshPtr mesh,
        size_t &vertexCount,
        Ogre::Vector3* &vertices,
        size_t &indexCount,
        unsigned* &indices) 
    {
        bool addShared = false;
        size_t currentOffset = 0;
        size_t shared_offset = 0;
        size_t nextOffset = 0;
        size_t indexOffset = 0;


        vertexCount = indexCount = 0;

        for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {
            Ogre::SubMesh* submesh = mesh->getSubMesh(i);
            if(submesh->useSharedVertices) {
                if( !addShared ) {
                    vertexCount += mesh->sharedVertexData->vertexCount;
                    addShared = true;
                }
            }
            else {
                vertexCount += submesh->vertexData->vertexCount;
            }
            indexCount += submesh->indexData->indexCount;
        }


        vertices = new Ogre::Vector3[vertexCount];
        indices = new unsigned[indexCount];

        addShared = false;

        for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i) {
            Ogre::SubMesh* submesh = mesh->getSubMesh(i);

            Ogre::VertexData* vertexData = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

            if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !addShared)) {
                if(submesh->useSharedVertices) {
                    addShared = true;
                    shared_offset = currentOffset;
                }

                const Ogre::VertexElement* posElem =
                    vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

                Ogre::HardwareVertexBufferSharedPtr vbuf =
                    vertexData->vertexBufferBinding->getBuffer(posElem->getSource());

                unsigned char* vertex =
                    static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

                float* pReal;

                for( size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vbuf->getVertexSize()) {
                    posElem->baseVertexPointerToElement(vertex, &pReal);
                    Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
                    vertices[currentOffset + j] = pt;
                }
                
                vbuf->unlock();
                nextOffset += vertexData->vertexCount;
            }


            Ogre::IndexData* indexData = submesh->indexData;
            size_t numTris = indexData->indexCount / 3;
            Ogre::HardwareIndexBufferSharedPtr ibuf = indexData->indexBuffer;
            
            bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

            unsigned long* pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

            size_t offset = (submesh->useSharedVertices)? shared_offset : currentOffset;

            if ( use32bitindexes ) {
                for ( size_t k = 0; k < numTris*3; ++k) {
                    indices[indexOffset++] = pLong[k] + static_cast<unsigned long>(offset);
                }
            }
            else {
                for ( size_t k = 0; k < numTris*3; ++k) {
                    indices[indexOffset++] = static_cast<unsigned long>(pShort[k]) +
                                              static_cast<unsigned long>(offset);
                }
            }

            ibuf->unlock();
            currentOffset = nextOffset;
        }
    }

}

