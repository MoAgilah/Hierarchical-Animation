#include "HeightMap.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

HeightMap::HeightMap( char* filename, float gridSize )
{
	LoadHeightMap(filename, gridSize);

	m_pHeightMapBuffer = NULL;

	static const VertexColour MAP_COLOUR(200, 255, 255, 255);

	XMFLOAT3 v0, v1, v2, v3, norm1, norm2;
	int mapIndex = 0;

	m_HeightMapVtxCount = (m_HeightMapLength - 1) * m_HeightMapWidth * 2;
	m_pMapVtxs = new Vertex_Pos3fColour4ubNormal3f[ m_HeightMapVtxCount ];

	m_pHeightMapNorms = new XMFLOAT3[m_HeightMapVtxCount];

	calculateNormals();

	for (int y = 0; y < m_HeightMapLength - 1; ++y)
	{
		for (int x = 0; x < m_HeightMapWidth; ++x)
		{
			//defines the position on the heightmap
			int pos = x + y * m_HeightMapWidth;

			//returns a vector of that position
			v0 = m_pHeightMap[pos];
			v1 = m_pHeightMap[pos + m_HeightMapWidth];
			v2 = m_pHeightMap[pos + 1];
			v3 = m_pHeightMap[pos + m_HeightMapWidth + 1];

			//loads float into vectors
			XMVECTOR vec0 = XMLoadFloat3(&v0);
			XMVECTOR vec1 = XMLoadFloat3(&v1);
			XMVECTOR vec2 = XMLoadFloat3(&v2);
			XMVECTOR vec3 = XMLoadFloat3(&v3);

			//calculates cross product	(v2 - v1 x v3 - v1)
			XMVECTOR tri1 = XMVector3Cross(vec1 - vec0, vec2 - vec0);

			//stores for use in float3 
			XMStoreFloat3(&norm1, tri1);


			XMVECTOR tri2 = XMVector3Cross(vec1 - vec2, vec3 - vec1);
			XMStoreFloat3(&norm2, tri2);


			;
			// Side 5 - Top face
			m_pMapVtxs[mapIndex + 0] = Vertex_Pos3fColour4ubNormal3f(v0, MAP_COLOUR, norm1);
			m_pMapVtxs[mapIndex + 1] = Vertex_Pos3fColour4ubNormal3f(v1, MAP_COLOUR, norm1);

			mapIndex += 2;
		}
		++y;
		for (int x = 0; x < m_HeightMapWidth; ++x)
		{
			if (y < m_HeightMapLength - 1)
			{
				const int pos = m_HeightMapWidth - 1 - x + (y * m_HeightMapWidth);

				//returns a vector of that position
				v0 = m_pHeightMap[pos];
				v1 = m_pHeightMap[pos + m_HeightMapWidth];
				v2 = m_pHeightMap[pos + 1];
				v3 = m_pHeightMap[pos + m_HeightMapWidth + 1];

				//loads float into vectors
				XMVECTOR vec0 = XMLoadFloat3(&v0);
				XMVECTOR vec1 = XMLoadFloat3(&v1);
				XMVECTOR vec2 = XMLoadFloat3(&v2);
				XMVECTOR vec3 = XMLoadFloat3(&v3);

				//calculates cross product	(v2 - v1 x v3 - v1)
				XMVECTOR tri1 = XMVector3Cross(vec1 - vec0, vec2 - vec0);
				//stores for use in float3 
				XMStoreFloat3(&norm1, tri1);


				XMVECTOR tri2 = XMVector3Cross(vec1 - vec2, vec3 - vec1);
				XMStoreFloat3(&norm2, tri2);

				// Side 5 - Top face
				m_pMapVtxs[mapIndex + 0] = Vertex_Pos3fColour4ubNormal3f(v0, MAP_COLOUR, norm1);
				m_pMapVtxs[mapIndex + 1] = Vertex_Pos3fColour4ubNormal3f(v1, MAP_COLOUR, norm1);

				//indicates 6 points have been added 
				mapIndex += 2;
			}
		}
	}

	delete m_pHeightMapNorms;
	m_pHeightMapBuffer = CreateImmutableVertexBuffer(Application::s_pApp->GetDevice(), sizeof Vertex_Pos3fColour4ubNormal3f * m_HeightMapVtxCount, m_pMapVtxs);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

HeightMap::~HeightMap()
{
	Release(m_pHeightMapBuffer);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void HeightMap::Draw( void )
{
	Application::s_pApp->DrawUntexturedLit(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, m_pHeightMapBuffer, NULL, m_HeightMapVtxCount);
}

//////////////////////////////////////////////////////////////////////
// LoadHeightMap
// Original code sourced from rastertek.com
//////////////////////////////////////////////////////////////////////
bool HeightMap::LoadHeightMap(char* filename, float gridSize )
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned char height;


	// Open the height map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Save the dimensions of the terrain.
	m_HeightMapWidth = bitmapInfoHeader.biWidth;
	m_HeightMapLength = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = m_HeightMapWidth * m_HeightMapLength * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	// Create the structure to hold the height map data.
	XMFLOAT3* pUnsmoothedMap = new XMFLOAT3[m_HeightMapWidth * m_HeightMapLength];
	m_pHeightMap = new XMFLOAT3[m_HeightMapWidth * m_HeightMapLength];

	if(!m_pHeightMap)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k=0;

	// Read the image data into the height map.
	for(j=0; j<m_HeightMapLength; j++)
	{
		for(i=0; i<m_HeightMapWidth; i++)
		{
			height = bitmapImage[k];
			
			index = (m_HeightMapWidth * j) + i;

			m_pHeightMap[index].x = (float)(i-(m_HeightMapWidth/2))*gridSize;
			m_pHeightMap[index].y = (float)height/6*gridSize;
			m_pHeightMap[index].z = (float)(j-(m_HeightMapLength/2))*gridSize;

			pUnsmoothedMap[index].y = (float)height/6*gridSize;

			k+=3;
		}
	}


	// Smoothing the landscape makes a big difference to the look of the shading
	for( int s=0; s<2; ++s )
	{
		for(j=0; j<m_HeightMapLength; j++)
		{
			for(i=0; i<m_HeightMapWidth; i++)
			{	
				index = (m_HeightMapWidth * j) + i;

				if( j>0 && j<m_HeightMapLength-1 && i>0 && i<m_HeightMapWidth-1 )
				{
					m_pHeightMap[index].y = 0.0f;
					m_pHeightMap[index].y += pUnsmoothedMap[index-m_HeightMapWidth-1].y	+ pUnsmoothedMap[index-m_HeightMapWidth].y + pUnsmoothedMap[index-m_HeightMapWidth+1].y;
					m_pHeightMap[index].y += pUnsmoothedMap[index-1].y	+ pUnsmoothedMap[index].y + pUnsmoothedMap[index+1].y;
					m_pHeightMap[index].y += pUnsmoothedMap[index+m_HeightMapWidth-1].y	+ pUnsmoothedMap[index+m_HeightMapWidth].y + pUnsmoothedMap[index+m_HeightMapWidth+1].y;
					m_pHeightMap[index].y /= 9;
				}		
			}
		}

		for(j=0; j<m_HeightMapLength; j++)
		{
			for(i=0; i<m_HeightMapWidth; i++)
			{	
				index = (m_HeightMapWidth * j) + i;
				pUnsmoothedMap[index].y = m_pHeightMap[index].y;
			}
		}

	}

	// Release the bitmap image data.
	delete [] bitmapImage;
	delete [] pUnsmoothedMap;
	bitmapImage = 0;

	return true;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void HeightMap::calculateNormals()
{
	XMFLOAT3 v0, v1, v2, v3, norm1;

	int mapIndex = 0;

	for (int y = 0; y < m_HeightMapLength - 1; ++y)
	{
		for (int x = 0; x < m_HeightMapWidth; ++x)
		{
			//defines the position on the heightmap
			int pos = x + y * m_HeightMapWidth;

			//returns a vector of that position
			v0 = m_pHeightMap[pos];
			v1 = m_pHeightMap[pos + m_HeightMapWidth];
			v2 = m_pHeightMap[pos + 1];
			v3 = m_pHeightMap[pos + m_HeightMapWidth + 1];

			//loads float into vectors
			XMVECTOR vec0 = XMLoadFloat3(&v0);
			XMVECTOR vec1 = XMLoadFloat3(&v1);
			XMVECTOR vec2 = XMLoadFloat3(&v2);
			XMVECTOR vec3 = XMLoadFloat3(&v3);

			//calculates cross product	(v2 - v1 x v3 - v1)
			XMVECTOR tri1 = XMVector3Cross(vec1 - vec0, vec2 - vec0);

			//stores for use in float3 
			XMStoreFloat3(&norm1, tri1);
	
			m_pHeightMapNorms[mapIndex + 0] = norm1;
			m_pHeightMapNorms[mapIndex + 1] = norm1;
			mapIndex += 2;
		}
		++y;
		for (int x = 0; x < m_HeightMapWidth; ++x)
		{
			if (y < m_HeightMapLength - 1)
			{
				const int pos = m_HeightMapWidth - 1 - x + (y * m_HeightMapWidth);

				//returns a vector of that position
				v0 = m_pHeightMap[pos];
				v1 = m_pHeightMap[pos + m_HeightMapWidth];
				v2 = m_pHeightMap[pos + 1];
				v3 = m_pHeightMap[pos + m_HeightMapWidth + 1];

				//loads float into vectors
				XMVECTOR vec0 = XMLoadFloat3(&v0);
				XMVECTOR vec1 = XMLoadFloat3(&v1);
				XMVECTOR vec2 = XMLoadFloat3(&v2);
				XMVECTOR vec3 = XMLoadFloat3(&v3);

				//calculates cross product	
				XMVECTOR tri1 = XMVector3Cross(vec2 - vec0, vec2 - vec1);
				
				m_pHeightMapNorms[mapIndex + 0] = norm1;
				m_pHeightMapNorms[mapIndex + 1] = norm1;
				mapIndex += 2;
			}
		}
	}
}
