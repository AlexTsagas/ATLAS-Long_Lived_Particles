// Functions for Vector Operations //

// Print array[3] elements
void printCoordinates(double *array)
{
    cout<<"("<<array[0]<<", "<<array[1]<<", "<<array[2]<<")"<<endl;
}


// Input two vectors with three coordinates each and output their dot product
double dotProduct(double *a, double *b)
{
    double dotproduct;

    dotproduct = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];

    return dotproduct;
}


// Input two vectors with three coordinates each and output a pointer to the
// first element of the array with three elements of their cross product
double *crossProduct(double *a, double *b)
{
    static double crossproduct[3];

    crossproduct[0] = a[1]*b[2] - a[2]*b[1];
    crossproduct[1] = a[2]*b[0] - a[0]*b[2];
    crossproduct[2] = a[0]*b[1] - a[1]*b[0];

    return crossproduct;
}


// Triple product between vectors a, b, c with three coordinates each. Triple
// product is defined as (a, b x c).
double tripleProduct(double *a, double *b, double *c)
{
    double *crossp = crossProduct(b, c);
    double cross[3] = {crossp[0], crossp[1], crossp[2]};

    double triple = dotProduct(a, cross);

    return triple;
}


// Input an array with three elements and output the norm sqrt{\vb{a}\cdot\vb{a}}
double norm(double *a)
{
    double norm;
    double dotp = dotProduct(a, a);

    norm = sqrt(dotp);

    return norm;
}


// Relative Vector that points from a to b
double *relativeVector(double *a, double *b)
{
    static double relative[3];
    for(int i=0; i<3; i++)
    {
        relative[i] = b[i] - a[i];
    }

    return relative;
}


// Input two vectors a, b with three elemets each. Output the unit vector that points
// from a to b.
double *unitVector(double *a)
{
    static double unitvector[3];

    double Norm = norm(a);

    for(int i=0; i<3; i++)
    {
        unitvector[i] = a[i]/Norm;
    }

    return unitvector;
}


//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// Input two points of the line, a and b. Ouput a pointer to the first element of
// the array containing line points in relation with t
double *lineEquation(double *a, double *b, double t)
{   
    // Parallel to line unit vector pointing from a to b
    double *N = relativeVector(a, b);
    double *n = unitVector(N);
   
    // The line point
    static double lineVector[3];
    for(int i=0; i<3; i++)
    {
        lineVector[i] = a[i] + t*n[i];
    }

    return lineVector;
}


// Calculates the distance of line1 which passes through r1, r11 and line2
// which passes through r2, r22.
double distance(double *r1, double *rr1, double *r2, double *rr2)
{
    // Parallel to line1
    double *N1p = relativeVector(r1, rr1);
    double N1[3] = {N1p[0], N1p[1], N1p[2]};
    
    // Parallel to line2
    double *N2p = relativeVector(r2, rr2);
    double N2[3] = {N2p[0], N2p[1], N2p[2]};

    // The point where the plane passes: r0 = r2 - r1
    double *r0p = relativeVector(r1, r2);
    double r0[3] = {r0p[0], r0p[1], r0p[2]};

    // Perpendicular to the plane
    double *u = crossProduct(N2, N1);

    double d = abs(dotProduct(r0, u))/norm(u);

    return d;
}


// Calculates the coordinates of the displaced vertex as the midpoint of AB, where
// |AB| is the distance between the lines.
double *displacedVertex(double *r1, double *rr1, double *r2, double *rr2)
{
    // Parallel to line1
    double *N1p = relativeVector(r1, rr1);
    double N1[3] = {N1p[0], N1p[1], N1p[2]};

    // Parallel to line2
    double *N2p = relativeVector(r2, rr2);
    double N2[3] = {N2p[0], N2p[1], N2p[2]};

    // The point where the plane passes: r0 = r2 - r1
    double *r0p = relativeVector(r1, r2);
    double r0[3] = {r0p[0], r0p[1], r0p[2]};

    // Perpendicular to the plane
    double *up = crossProduct(N2, N1);
    double u[3] = {up[0], up[1], up[2]};

    // Argument to find A
    double t0 = tripleProduct(u, N2, r0)/(norm(u)*norm(u));

    // Line1 point A
    double OA[3];
    for(int i=0; i<3; i++)
    {
        OA[i] = r1[i] + t0*N1[i];
    }

    // Argument to find B
    double s0 = tripleProduct(u, N1, r0)/(norm(u)*norm(u));

    // Line2 point B
    double OB[3];
    for(int i=0; i<3; i++)
    {
        OB[i] = r2[i] + s0*N2[i];
    }

    static double displacedvertex[3];
    for(int i=0; i<3; i++)
    {
        displacedvertex[i] = 0.5*(OA[i] + OB[i]);
    }

    return displacedvertex;
}


//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// Computes the minimum value of array's first column distance[elementCount][3] and stores
// the indexes of the same row.
double *minimumArrayValue(double distance[][3], int elementCount)
{
    // First element the minimum value. Second and third the indexes of disranceelementCount3]
    // in the same row.
    static double minimum[3];

    // Initialize with the first row of distance[elementCount][3]
    minimum[0] = distance[0][0];
    minimum[1] = distance[0][1];
    minimum[2] = distance[0][2];

    // Go throught the array
    double element;

    for(int i=1; i<elementCount; i++)
    {
        element = distance[i][0];

        if(minimum[0] >= element)
        {
            minimum[0] = element;
            minimum[1] = distance[i][1];
            minimum[2] = distance[i][2];
        }
    }

    return minimum;
}


// Calculates the distance between Point1(x1, y1, z1) and (x2, y2, z2)
double Error(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double error;
 
    error = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));

    return error;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Readers to access the data
TTreeReader treereader;

TTreeReaderValue<ULong_t> eventNumber = {treereader, "eventNumber"};
TTreeReaderValue<Int_t> track_n = {treereader, "track_n"};
TTreeReaderValue<Int_t> truthvtx_n = {treereader, "truthvtx_n"};
TTreeReaderArray<Double_t> track_x0 = {treereader, "track.x0"};
TTreeReaderArray<Double_t> track_y0 = {treereader, "track.y0"};
TTreeReaderArray<Double_t> track_z0 = {treereader, "track.z0"};
TTreeReaderArray<Double_t> track_x1 = {treereader, "track.x1"};
TTreeReaderArray<Double_t> track_y1 = {treereader, "track.y1"};
TTreeReaderArray<Double_t> track_z1 = {treereader, "track.z1"};
TTreeReaderArray<Double_t> truthvtx_x = {treereader, "truthvtx.x"};
TTreeReaderArray<Double_t> truthvtx_y = {treereader, "truthvtx.y"};
TTreeReaderArray<Double_t> truthvtx_z = {treereader, "truthvtx.z"};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

void newmyAnalyzeStage1()
{
    // For time capture
    clock_t tStart = clock();

    TH2 *H = new TH2D("H", "Absolute Error In Relation to (Minimum) Distance of Trajectories;Distance;Absolute Error;Count", 20, 0, 0.15, 30, 0, 6.5);
    TH1 *h1 = new TH1D("h1", "Absolute Error;Error;Counts", 50, 0, 6.5);
    TH1 *h2 = new TH1D("hist", "Minimum Trajectory Distance to Each Event;Distance;Counts", 40, 0, 0.15);

    TFile* infile = TFile::Open("stage1.root");
    TTree* tree   = (TTree*)infile->Get("stage1");
    treereader.SetTree(tree);

    // Line_i Points
    double a[3], b[3];
    // Line_j Points
    double aa[3], bb[3];

    // Array that gathers the distances between line i and j and stores them in the first column.
    //  The second and the third column store information about line_i and line_j, respectively (the index).
    double distance_ij[100][3];
    // Elements Counter for distance_ij
    int elementCount;
    // Counters for distance_ij array elemets
    int count_j;


    // The minimum distance of all the possible pair of lines for every event (total events = 4299)
    // The first column contains the least distance for every event. The other two to which two lines
    // it is refering to (the indexes).
    double leastDistance[4299][3];
    double *least_Distance;


    // Stores the coordinates of each displaced vertex of any event in rows
    double displacedVertexArray[4299][3];
    double *displaced_Vertex;

    double A[3], B[3];
    double AA[3], BB[3];
    // Counters
    int I, J;


    // The distance of the truth displaced vertex from the calculated displaced vertex.
    // The m^th element is the calculated error of m^th event
    double absoluteError[4299];

    
    // Event Counter
    int event = 0;

    // Integers for for loops
    int i, j;


    while (treereader.Next()) 
    {
        if(*truthvtx_n==1) 
        {   
            count_j = 0;

            for(i=0; i<*track_n; i++)
            {
                a[0] = track_x0[i]; a[1] = track_y0[i]; a[2] = track_z0[i];
                b[0] = track_x1[i]; b[1] = track_y1[i]; b[2] = track_z1[i];

                for(j=i+1; j<*track_n; j++)
                {   
                    aa[0] = track_x0[j]; aa[1] = track_y0[j]; aa[2] = track_z0[j];
                    bb[0] = track_x1[j]; bb[1] = track_y1[j]; bb[2] = track_z1[j];

                    distance_ij[count_j][0] = distance(a, b, aa, bb);
                    distance_ij[count_j][1] = i;
                    distance_ij[count_j][2] = j;

                    count_j++;
                }
            }

            // The number of elements in distance_ij columns
            elementCount = count_j;

            least_Distance = minimumArrayValue(distance_ij, elementCount);

            leastDistance[event][0] = least_Distance[0];    // distance for event
            leastDistance[event][1] = least_Distance[1];    // index of line_i 
            leastDistance[event][2] = least_Distance[2];    // index of line_j

            h2->Fill(leastDistance[event][0]);

            // To find th displaced vertex coordinates
            I = leastDistance[event][1];
            J = leastDistance[event][2];

            A[0] = track_x0[I]; A[1] = track_y0[I]; A[2] = track_z0[I];
            B[0] = track_x1[I]; B[1] = track_y1[I]; B[2] = track_z1[I];
            AA[0] = track_x0[J]; AA[1] = track_y0[J]; AA[2] = track_z0[J];
            BB[0] = track_x1[J]; BB[1] = track_y1[J]; BB[2] = track_z1[J];

            displaced_Vertex = displacedVertex(A, B, AA, BB);
            displacedVertexArray[event][0] = displaced_Vertex[0];
            displacedVertexArray[event][1] = displaced_Vertex[1];
            displacedVertexArray[event][2] = displaced_Vertex[2];

            absoluteError[event] = Error(displacedVertexArray[event][0], displacedVertexArray[event][1], displacedVertexArray[event][2], truthvtx_x[0], truthvtx_y[0], truthvtx_z[0]);

            h1->Fill(absoluteError[event]);

            H->Fill(leastDistance[event][0], absoluteError[event]);

            event++;
        }
    }

    TCanvas *c = new TCanvas("c", "Distance - Absolute Error", 1200, 500);
    c->Divide(3,1);

    c->cd(1);
    h1->SetFillColor(kBlue-2);
    h1->SetMinimum(0);
    h1->Draw();

    c->cd(2);
    h2->SetFillColor(kGreen-7);
    h2->SetMinimum(0);
    h2->Draw();

    c->cd(3);
    H->SetFillColor(kRed);
    H->SetMinimum(0);
    H->Draw("LEGO1");

    // Print time needed for the program to complete
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    infile->Close();
    }