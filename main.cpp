#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

GLfloat texture[10];
GLfloat skybox[6];

const int ParticleCount = 500;
const int CometCount=4;

typedef struct
{
    double Xpos;
    double Ypos;
    double Zpos;
    double Xmov;
    double Zmov;
    double Red;
    double Green;
    double Blue;
    double Direction;
    double Acceleration;
    double Deceleration;
    double Scalez;
    bool Visible;
} PARTICLES;

PARTICLES Particle[ParticleCount];
PARTICLES comet[CometCount];

GLuint LoadTextureRAW( const char * filename, int width,
                       int height);
void FreeTexture( GLuint texturez );

void square (void)
{
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0);
    glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0);
    glVertex2d(1.0,-1.0);
    glTexCoord2d(1.0,1.0);
    glVertex2d(1.0,1.0);
    glTexCoord2d(0.0,1.0);
    glVertex2d(-1.0,1.0);
    glEnd();
}


void glCreatecomet(void)
{
    int i;
    for (i = 1; i < CometCount; i++)
    {
        comet[i].Xpos = 30;
        comet[i].Ypos = 20;
        comet[i].Zpos = -10;
        comet[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                           rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                         ) * rand()%11) + 1) * 0.005);
        comet[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                           rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                         ) * rand()%11) + 1) * 0.005);
        comet[i].Red = 1;
        comet[i].Green = 1;
        comet[i].Blue = 1;
        comet[i].Scalez = 0.25;//0.25;
        comet[i].Direction = 0;
        comet[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                   ) - 1 + 1) * rand()%11) + 1) * 0.02;
        comet[i].Deceleration = 0.0025;
    }
}

void glUpdateComet (void)
{
    int i;
    for (i = 1; i < CometCount; i++)
    {

        glColor3f (comet[i].Red, comet[i].Green,
                   comet[i].Blue);

        comet[i].Ypos = comet[i].Ypos - comet[i]
                        .Acceleration ;//- comet[i].Deceleration;
        comet[i].Xpos = comet[i].Ypos + comet[i].Acceleration ;//- comet[i].Deceleration;

        comet[i].Deceleration = comet[i].Deceleration +
                                0.0025;

        comet[i].Xpos = comet[i].Xpos + comet[i].Xmov;
        comet[i].Zpos = comet[i].Zpos + comet[i].Zmov;

        comet[i].Direction = comet[i].Direction + ((((((int
                                                       )(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);

//if (comet[i].Ypos < -5)
        if (comet[i].Ypos <-15)
        {
            comet[i].Xpos = 30;
            comet[i].Ypos = 20;
            comet[i].Zpos = -10;
            comet[i].Red = 1;
            comet[i].Green = 1;
            comet[i].Blue = 1;
            comet[i].Direction = 0;
            comet[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                       ) - 1 + 1) * rand()%11) + 1) * 0.02;
            comet[i].Deceleration = 0.0025;
        }

    }
}

void glCreateParticles (void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        Particle[i].Xpos = 0;
        Particle[i].Ypos = 0;
        Particle[i].Zpos = 0;
        Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        Particle[i].Red = 1;
        Particle[i].Green = 1;
        Particle[i].Blue = 1;
        Particle[i].Scalez = 0.25;//0.25;
        Particle[i].Direction = 0;
        Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                      ) - 1 + 1) * rand()%11) + 1) * 0.02;
        Particle[i].Deceleration = 0.0025;
    }
}

void glUpdateParticles (void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {

        glColor3f (Particle[i].Red, Particle[i].Green,
                   Particle[i].Blue);

        Particle[i].Ypos = Particle[i].Ypos + Particle[i]
                           .Acceleration ;//- Particle[i].Deceleration;
        Particle[i].Deceleration = Particle[i].Deceleration +
                                   0.0025;

        Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
        Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;

        Particle[i].Direction = Particle[i].Direction + ((((((int
                                                             )(0.5 - 0.1 + 0.1) * rand()%5) + 1) - 1 + 1)* rand()%5) + 1);//Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1)* rand()%11) + 1);

//if (Particle[i].Ypos < -5)
        if (Particle[i].Ypos >55)
        {
            Particle[i].Xpos = 0;
            Particle[i].Ypos = 0;
            Particle[i].Zpos = 0;
            Particle[i].Red = 1;
            Particle[i].Green = 1;
            Particle[i].Blue = 1;
            Particle[i].Direction = 0;
            Particle[i].Acceleration =  ((((((20 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;//((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
            Particle[i].Deceleration = 0.0025;
        }

    }
}

void glDrawParticles (void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        glPushMatrix();

        glTranslatef (Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
        glRotatef (Particle[i].Direction +270, 0, 0, 1);

        glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);

        glDisable (GL_DEPTH_TEST);
        glEnable (GL_BLEND);

        glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBindTexture (GL_TEXTURE_2D, texture[0]);

        glBegin (GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f (-1, -1, 0);
        glTexCoord2d (1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();


        glBlendFunc (GL_ONE, GL_ONE);
        glBindTexture (GL_TEXTURE_2D, texture[1]);

        glBegin (GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f (-1, -1, 0);
        glTexCoord2d (1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();


        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glPopMatrix();

    }
}

void glDrawComet (void)
{
    int i;
    for (i = 1; i < CometCount; i++)
    {
        glPushMatrix();

        glTranslatef (comet[i].Xpos, comet[i].Ypos, comet[i].Zpos);
        //glRotatef (comet[i].Direction -90, 0, 1, 0);

        glScalef (comet[i].Scalez, comet[i].Scalez, comet[i].Scalez);

        glDisable (GL_DEPTH_TEST);
        glEnable (GL_BLEND);

        //glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBindTexture (GL_TEXTURE_2D, texture[1]);

        glRotatef(45,1,1,0);


        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0f,1.0f,-1.0f);//glVertex3f(1.0f,1.0f,-1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0f,1.0f,-1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-2.0f,3.0f,1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f,2.0f,1.0f);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0f,-1.5f,1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0f,-2.0f,1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f,-1.0f,-1.0f);


        //blue front
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0f,2.0f,1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-2.0f,3.0f,1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0f,-2.0f,1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f,-1.5f,1.0f);
// white back
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0f,-1.0f,-1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0f,1.0f,-1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f,1.0f,-1.0f);

        //lightblue left
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-2.0f,3.0f,1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0f,1.0f,-1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1.0f,-2.0f,1.0f);

        //yellow right
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0f,1.0f,-1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1.0f,2.0f,1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0f,-1.5f,1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f,-1.0f,-1.0f);

        glEnd();



        glEnable(GL_DEPTH_TEST);

        glRotatef(-30,0,0,1); // give the rotation of 30
        glTranslatef(-1,-1,0);
        glDrawParticles();
        glPopMatrix();





    }
}








void display (void)
{
    glClearDepth (1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
     glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);




    glTranslatef (0,0,-10);

    glUpdateParticles();

    glUpdateComet();

    glDrawComet();
    glTranslatef(0,0,-35);
   // glutSolidSphere(10,30,30);
     // glDrawWorld();
    // glDrawParticles();

    glutSwapBuffers();
}

void init (void)
{
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_DEPTH_TEST);

    glCreateParticles();
    glCreatecomet();

    texture[0] = LoadTextureRAW( "C:\\Users\\user\\Desktop\\degree year 2 sem 3\\house texturing.bmp",256,256
                               ); //load our texture
    texture[1] = LoadTextureRAW( "C:\\Users\\user\\Desktop\\degree year 2 sem 3\\house texturing\\door.bmp",256,256);

   // texture[2] = LoadTextureRAW( "C:\\Users\\user\\Desktop\\degree year 2 sem 3\\mp_moondust\\moondust_bk.tga",256,256);


//load our texture
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
    glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutMainLoop ();
     FreeTexture(texture[1]);

    return 0;
}

//function to load the RAW file

GLuint LoadTextureRAW( const char * filename, int width,
                       int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    file = fopen( filename, "rb" );
    if ( file == NULL )
        return 0;

    data = (unsigned char *)malloc( width * height * 3 );

    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures(1, &texture );

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     GL_REPEAT);

    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
               GL_MODULATE );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                     GL_LINEAR );

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
                      GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data );

    return texture;
}

void FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );
}
