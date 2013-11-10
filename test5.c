#include <stdio.h>
#include <stdlib.h>



// ==========================================
//
//  HEADER FILE STUFF
//
//
// ==========================================

// die with some purpose / explanation

static void die(char *message)
{
   printf("ppm: %s\n", message);
   exit(1);
} // end die

static void checkSize(int dim)
{
   if ((dim < 1) || (dim > 700)) {
        die("file has unreasonble width or height");
   } // end if dim
} // end checkSize

int readImageHeader( char  file_name ) {

       FILE * file = fopen( file_name, "r" );

        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else
        {
           printf("file opened... read header information\n\n");

           char ch;
           int maxval, width, height;

            // read the width, height and maxvalue

            char letter_type;
            fscanf(file, "%c", &letter_type);
            int number_type;
            fscanf(file, "%d", &number_type);

            ch = getc(file);
            while (ch == '#')
            { do {
               ch = getc(file);
            } while (ch != '\n');
               ch = getc(file);
            } // end finding comment while

            fscanf(file, "%d %d %d\n", &width, &height, &maxval);
            printf ("Image %c%d - %d %d %d\n\n", letter_type, number_type, width, height, maxval);
            fclose( file );
            }

return;
} // end readImageHeader

int readImageData( char * file_name) {


} // end readImageData

int writeNewImage( char * new_file ) {

} // endwriteNewImage

// =====================================
// END OF HEADER FILE STUFF
// =====================================


// ==========================================
//
//  mirror.c
//
//
// ==========================================

static void mirrorImage( char * file_name ) {


} // end mirorrImage

// ==========================================
//  END OF MIRROR.C
// ==========================================

// ==========================================
//
//  gray.c
//
//
// ==========================================

static void grayImage( char * file_name ) {


} // end grayImage

// ==========================================
//  END OF gray.C
// ==========================================

// ==========================================
//
//  rotate.c
//
//
// ==========================================

static void rotateImage( char * file_name ) {


} // end rotateImage

// ==========================================
//  END OF rotate.C
// ==========================================

int main ( int argc, char *argv[] ) {

    int debug = 1;
    char fname;
    int  selection;

    sscanf(argv[1], "%d", &selection);
    sscanf(argv[2], "%s", &fname)

    // check that you have correct input from command line
    if ( argc != 3 ) /* argc should be 3 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        die("\n\nFail - incorrect input, ex 1 file.ppm > new_file.ppm\n\n");
    }
    else
    {
       if (debug) { printf( "\n\nArg values %s :: %s\n\n", argv[1], argv[2]);}
          fname = argv[2];
          readImageHeader(fname);
    } // end if argc

    if (debug) {printf("\n Selection: %s / %d\n", argv[1], selection);}

    if (argv[1] == "1")
    {
    //  flip image along vertical axis  (mirror.c)
        mirrorImage(fname);
    } else if (argv[1] == "2") {
    //  create greay scale version of image  (gray.c)
       grayImage(fname);

    } else if (argv[1] == "3") {
    // rotate image 90 degrees to the left   (rotate.c)
       rotateImage(fname);

    } else {
    // did not get an appropriate directive
    die("\n\nSorry, enter directive 1, 2 or 3 only\n\n");

    } // end if selection


return(0);
}
