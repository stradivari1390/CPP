/**
 * This program performs various operations on a graph.
 */

#include <iostream>
#include "dos.h"
#include "graphics.h"
#include "conio.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cctype>
#include "dir.h"
#include "winbgim.h"
#include <ctime>
#include <fstream>

int testInput();

int charToInt(char *);

void displayMenu(int);

void exitProgram(clock_t);

void searchFile();

int setColor(int);

class Graph {
private:
    int numVertices;
    int **adjacencyMatrix;
public:
    Graph();

    Graph(int, int);                      // Number of vertices , 0 - no edges, 1 - all edges connected;
    Graph(char *, int);                   // Name of file , 0 - adjacency , 1 - incidence
    Graph(const Graph &);                 // Copy constructor
    ~Graph();                             // Destructor
    Graph& operator=(const Graph&);               // Operator =
    void addVertex();                     // Add Extra Vertex to Graph
    void addEdge(int, int);               // Add Extra Edge to Graph
    void removeVertex(int);               // Remove Vertex from Graph
    void removeEdge(int, int);            // Remove Edge from Graph
    int checkTrivial(int, int);           // Checking on Triviality
    void searchTrivial();                 // Searching for Trivial vertices in Graph
    int checkAdjacency(int, int, int);    // Check if Vertices are adjacent or not
    int checkComplete(int);               // Check on complete graph or not
    void checkIsomorphism(const Graph&, Graph);  // Check on isomorphism
    void save(std::ostream &);            // Save
    void load(std::istream &);            // Load
    void info();                          // Information about Graph
    void display(int, int);               // Display
    void displayAlternative(int, int);    // Another one
};

//---------------------------------------------------------
//---------------------------------------------------------
Graph::Graph() {
    numVertices = 1;
    adjacencyMatrix = new int *[1];
    adjacencyMatrix[0] = new int[1];
    adjacencyMatrix[0][0] = 0;
}

//-------------------------------------
//-------------------------------------
Graph::Graph(int a, int adjanum) {
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    numVertices = a;
    adjacencyMatrix = new int *[numVertices];
    for (i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[numVertices];
    }
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            if (i == j) adjacencyMatrix[i][j] = 0;
            else adjacencyMatrix[i][j] = adjanum;
        }
    }
}

//-------------------------------------
//-------------------------------------
Graph::Graph(char *filename, int opr) {
    int i = 0;                   // For counting
    int j = 0;                   // =-=-=-=-=-=-=
    std::ifstream in(filename);
    if (!in) {
        std::cout << "Cant open file" << std::endl;
    }
    while (in.good()) {
        i++;
        while (in.good() && in.get() != '\n') continue;
    }
    numVertices = i;
    i = 0;
    in.clear();
    in.seekg(0, std::ios::beg);
    if (opr == 0) {
        adjacencyMatrix = new int *[numVertices];
        for (i = 0; i < numVertices; i++) {
            adjacencyMatrix[i] = new int[numVertices];
        }
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                in >> adjacencyMatrix[i][j];
            }
        }
    } else {
        int **mat = NULL;                      // Matrix of incidence
        int rib = 0;                           // Amount of ribs
        char help[5];                          // For proper count of ribs
        int x = 0;                             // For proper transformation
        int y = 0;                             // =-=-=-=-=-=-=
        int count = 0;                         // =-=-=-=-=-=-=
        int stop = 0;                          // =-=-=-=-=-=-=
        while (!in.eof()) {
            in >> help;
            i++;
        }
        rib = i / numVertices;
        in.clear();
        in.seekg(0, std::ios::beg);
        mat = new int *[rib];
        for (i = 0; i < rib; i++) {
            mat[i] = new int[numVertices];
        }
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < rib; j++) {
                in >> mat[j][i];
            }
        }
        adjacencyMatrix = new int *[numVertices];
        for (i = 0; i < numVertices; i++) {
            adjacencyMatrix[i] = new int[numVertices];
        }
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
        for (i = 0; i < rib; i++) {
            x = y = count = stop = 0;
            for (j = 0; j < numVertices && stop == 0; j++) {
                if (mat[i][j] == 1) {
                    x = j;
                    count++;
                }
                if (mat[i][j] == -1) {
                    y = j;
                    count++;
                }
                if (mat[i][j] == 2) {
                    x = j;
                    y = j;
                    count = 2;
                }
                if (count == 2) {
                    adjacencyMatrix[x][y] = 1;
                    stop = 1;
                }
            }
        }
    }
}

//-------------------------------------
//-------------------------------------
Graph::Graph(const Graph &a) {
    int i = 0;                              // For counting
    int j = 0;                   // =-=-=-=-=-=-=
    numVertices = a.numVertices;
    adjacencyMatrix = new int *[a.numVertices];
    for (i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[a.numVertices];
    }
    for (i = 0; i < a.numVertices; i++) {
        for (j = 0; j < a.numVertices; j++) {
            adjacencyMatrix[i][j] = a.adjacencyMatrix[i][j];
        }
    }
}

//-------------------------------------
//-------------------------------------
Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

//-------------------------------------
//-------------------------------------
Graph& Graph::operator=(const Graph &a) {
    if (this != &a) {
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;

        numVertices = a.numVertices;
        adjacencyMatrix = new int *[a.numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyMatrix[i] = new int[a.numVertices];
        }
        for (int i = 0; i < a.numVertices; i++) {
            for (int j = 0; j < a.numVertices; j++) {
                adjacencyMatrix[i][j] = a.adjacencyMatrix[i][j];
            }
        }
    }
    return *this;
}
//-------------------------------------
//-------------------------------------
void Graph::addVertex() {
    int **tempMatrix = NULL;              // Temporary matrix
    numVertices++;
    tempMatrix = new int *[numVertices];
    for (int i = 0; i < numVertices; i++) {
        tempMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            tempMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numVertices - 1; j++) {
            tempMatrix[i][j] = adjacencyMatrix[i][j];
        }
    }
    adjacencyMatrix = tempMatrix;
}

//-------------------------------------
//-------------------------------------
void Graph::addEdge(int a, int b) {
    if (a <= numVertices && b <= numVertices && a > 0 && b > 0) {
        adjacencyMatrix[a - 1][b - 1] = 1;
    } else {
        system("clear");
        std::cout << "U cant add rib to not exists vertex" << std::endl;
        getch();
    }
}

//-------------------------------------
//-------------------------------------
void Graph::removeVertex(int a) {
    if (a <= numVertices && a > 0) {
        int i = 0;                             // For counting
        int j = 0;                             // =-=-=-=-=-=-=
        int **helprem = NULL;                  // Extra massive
        numVertices--;
        a--;
        helprem = new int *[numVertices];
        for (i = 0; i < numVertices; i++) {
            helprem[i] = new int[numVertices];
        }
        for (i = 0; i < numVertices + 1; i++) {
            for (j = 0; j < numVertices + 1; j++) {
                if (a < i && a < j) {
                    helprem[i - 1][j - 1] = adjacencyMatrix[i][j];
                }
                if (a > i && a > j) {
                    helprem[i][j] = adjacencyMatrix[i][j];
                }
                if (a < i && a > j) {
                    helprem[i - 1][j] = adjacencyMatrix[i][j];
                }
                if (a < j && a > i) {
                    helprem[i][j - 1] = adjacencyMatrix[i][j];
                }
            }
        }
        adjacencyMatrix = helprem;
    } else {
        system("clear");
        std::cout << "U cant remove not exists vertex" << std::endl;
        getch();
    }
}

//-------------------------------------
//-------------------------------------
void Graph::removeEdge(int a, int b) {
    if (a <= numVertices && b <= numVertices && a > 0 && b > 0) {
        adjacencyMatrix[a - 1][b - 1] = 0;
    } else {
        system("clear");
        std::cout << "U cant remove rib between nonexists vertexes" << std::endl;
        getch();
    }
}

//-------------------------------------
//-------------------------------------
int Graph::checkTrivial(int a, int show) {
    int check = 0;                          // For check
    int i = 0;                              // For counting
    for (i = 0, check = 0; i < numVertices; i++) {
        if (adjacencyMatrix[a - 1][i] != 0 || adjacencyMatrix[i][a - 1] != 0) check = 1;
    }
    if (check == 1) {
        if (show == 0) {
            std::cout << "Point # " << a << " NOT trivial" << std::endl;
            getch();
        }
        return 1;
    } else {
        if (show == 0) {
            std::cout << "Point # " << a << " trivial" << std::endl;
            getch();
        }
        return 0;
    }
}

//-------------------------------------
//-------------------------------------
void Graph::searchTrivial() {
    int *search = NULL;                     // Massiv for save vertexes
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    int check = 0;                          // For check if this vertex or not
    int anscheck = 0;                       // Check if we found any
    search = new int[numVertices];
    for (i = 0; i < numVertices; i++) {
        search[i] = 0;
    }
    for (i = 0; i < numVertices; i++) {
        for (j = 0, check = 0; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] != 0 || adjacencyMatrix[j][i] != 0) check = 1, anscheck = 1;
        }
        if (check == 0) search[i] = 1;
    }
    if (anscheck == 0) {
        std::cout << "Trivial vertices: ";
        for (i = 0; i < numVertices; i++) {
            if (search[i] == 1) std::cout << i + 1 << " ";
        }
        std::cout << std::endl;
    } else std::cout << "Graph dont have any trivial vertexs" << std::endl;
}

//-------------------------------------
//-------------------------------------
int Graph::checkAdjacency(int a, int b, int show) {
    if (adjacencyMatrix[a - 1][b - 1] == 1 || adjacencyMatrix[b - 1][a - 1] == 1) {
        if (show == 0) {
            std::cout << a << "&" << b << " - adjacent verticals" << std::endl;
            getch();
        }
        return 0;
    } else {
        if (show == 0) {
            std::cout << a << "&" << b << " - NOT adjacent verticals" << std::endl;
            getch();
        }
        return 1;
    }
}

//-------------------------------------
//-------------------------------------
int Graph::checkComplete(int show) {
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    int check = 0;                          // For check
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            if (i != j) {
                if (adjacencyMatrix[i][j] + adjacencyMatrix[j][i] < 1) {
                    check = 1;
                }
            }
        }
    }
    if (check == 0) {
        if (show == 0) {
            std::cout << "Its full Graph" << std::endl;
            getch();
        }
        return 0;
    } else {
        if (show == 0) {
            std::cout << "Its NOT full Graph" << std::endl;
            getch();
        }
        return 1;
    }
}

//-------------------------------------
//-------------------------------------
void Graph::checkIsomorphism(const Graph&, Graph) {

}

//-------------------------------------
//-------------------------------------
void Graph::save(std::ostream &out) {
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    out << numVertices << " ";
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            out << adjacencyMatrix[i][j] << " ";
        }
    }
}

//-------------------------------------
//-------------------------------------
void Graph::load(std::istream &in) {
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    in >> numVertices;
    adjacencyMatrix = new int *[numVertices];
    for (i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[numVertices];
    }
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            in >> adjacencyMatrix[i][j];
        }
    }
}

//-------------------------------------
//-------------------------------------
void Graph::info() {
    if (checkComplete(1) == 0) {
        std::cout << "FULL" << std::endl;
    }
}

//-------------------------------------
//-------------------------------------
void Graph::display(int setup, int setupnumber) {
    int gdriver = DETECT;                 // Init Graphics screen
    int gmode;                            // =-=-=-=-=-=-=
    int errorcode;                        // For error with screen creating
    int xmid = 0;                           // Midle of screen by OX
    int ymid = 0;                           // Midle of screen by OY
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    int *x = NULL;                          // To place vertexes
    int *y = NULL;                          // =-=-=-=-=-=-=
    int len = 0;                            // For number
    char numbah[3];                       // =-=-=-=-=-=-=
    int arrowy = 0;                         // For arrows
    int arrowx = 0;                         // =-=-=-=-=-=-=
    double tg = 0.0;                        // =-=-=-=-=-=-=
    int drawornot = 0;                      // Draw or not check
    int graphcolor[4];                    // For Graph coloring
    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();
    if (errorcode != grOk) {
        std::cout << "Graphics error: %s" << std::endl << grapherrormsg(errorcode);
        std::cout << "Press any key to exit:";
        getch();
        exit(1);
    }
    std::ifstream gracolor("GRAPHOPT.txt");
    if (!gracolor) {
        std::cout << "Cant open file" << std::endl;
        getch();
    }
    gracolor.ignore(99, 'C');
    gracolor >> graphcolor[0];
    gracolor.ignore(99, 'D');
    gracolor >> graphcolor[1];
    gracolor.ignore(99, 'E');
    gracolor >> graphcolor[2];
    gracolor.ignore(99, 'F');
    gracolor >> graphcolor[3];
    gracolor.close();
    setcolor(graphcolor[0]);
    xmid = getmaxx() / 2;
    ymid = getmaxy() / 2;
    x = new int[numVertices];
    y = new int[numVertices];
    for (i = 0; i < numVertices; i++) {
        x[i] = xmid + 225 * cos((2 * M_PI * i) / numVertices);
        y[i] = ymid + 225 * sin((2 * M_PI * i) / numVertices);
        setfillstyle(1, graphcolor[0]);
        fillellipse(x[i], y[i], 15, 15);
    }
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            drawornot = 0;
            if (i != setupnumber - 1 && j != setupnumber - 1 && setup == 1) {
                drawornot = 1;
            }
            if (drawornot == 0) {
                if (adjacencyMatrix[j][i] != 0) {
                    if (j == i) {
                        if (x[i] <= xmid) {
                            ellipse(x[i] - 15, y[i], 0, 360, 20, 15);
                        } else {
                            ellipse(x[i] + 15, y[i], 0, 360, 20, 15);
                        }
                    } else {
                        setcolor(graphcolor[1]);
                        line(x[i], y[i], x[j], y[j]);
                        arrowy = abs((y[j] - y[i]) / 6);
                        arrowx = abs((x[j] - x[i]) / 6);
                        if (y[i] > y[j]) {
                            arrowy -= y[i];
                        } else {
                            arrowy += y[i];
                        }
                        if (x[i] > x[j]) {
                            arrowx -= x[i];
                        } else {
                            arrowx += x[i];
                        }
                        arrowy = abs(arrowy);
                        arrowx = abs(arrowx);
                        if (x[j] - x[i] != 0) {
                            tg = atan(-(y[j] - y[i]) / (x[j] - x[i])) * 180 / M_PI;
                        } else {
                            if (y[i] < arrowy) {
                                tg = -90;
                            } else {
                                tg = 90;
                            }
                        }
                        if (x[j] < arrowx) {
                            tg += 180;
                        }
                        setcolor(graphcolor[2]);
                        if (tg < 180) {
                            ellipse(arrowx, arrowy, tg + 90, tg + 270, 4, 4);
                        } else {
                            ellipse(arrowx, arrowy, tg - 270, tg - 90, 4, 4);
                        }
                    }
                }
            }
        }
    }
    setcolor(graphcolor[3]);
    settextstyle(0, 0, 2);
    for (i = 0; i < numVertices; i++) {
        sprintf(numbah, "%d", i + 1);
        len = strlen(numbah);
        outtextxy(x[i] - 7 * len, y[i] - 7, numbah);
    }
    getch();
    closegraph();
}

//---------------------------------------------------------
//---------------------------------------------------------
void Graph::displayAlternative(int setup, int setupnumber) {
    int gdriver = DETECT;                 // Init Graphics screen
    int gmode;                            // =-=-=-=-=-=-=
    int errorcode;                        // For error with screen creating
    int xmid = 0;                           // Midle of screen by OX
    int ymid = 0;                           // Midle of screen by OY
    int i = 0;                              // For counting
    int j = 0;                              // =-=-=-=-=-=-=
    int *x = NULL;                          // To place vertexes
    int *y = NULL;                          // =-=-=-=-=-=-=
    int len = 0;                            // For number
    char numbah[3];                       // =-=-=-=-=-=-=
    int arrowy = 0;                         // For arrows
    int arrowx = 0;                         // =-=-=-=-=-=-=
    double tg = 0.0;                        // =-=-=-=-=-=-=
    int drawornot = 0;                      // Draw or not check
    int graphcolor[4];                    // For Graph coloring
    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();
    if (errorcode != grOk) {
        std::cout << "Graphics error: %s" << std::endl << grapherrormsg(errorcode);
        std::cout << "Press any key to exit:";
        getch();
        exit(1);
    }
    std::ifstream gracolor("GRAPHOPT.txt");
    if (!gracolor) {
        std::cout << "Cant open file" << std::endl;
        getch();
    }
    gracolor.ignore(99, 'C');
    gracolor >> graphcolor[0];
    gracolor.ignore(99, 'D');
    gracolor >> graphcolor[1];
    gracolor.ignore(99, 'E');
    gracolor >> graphcolor[2];
    gracolor.ignore(99, 'F');
    gracolor >> graphcolor[3];
    gracolor.close();
    setcolor(graphcolor[0]);
    xmid = getmaxx() / 2;
    ymid = getmaxy() / 2;
    x = new int[numVertices];
    y = new int[numVertices];
    for (i = 0; i < numVertices; i++) {
        x[i] = xmid + 225 * cos((2 * M_PI * i) / numVertices);
        y[i] = ymid + 225 * sin((2 * M_PI * i) / numVertices);
        setfillstyle(1, graphcolor[0]);
        fillellipse(x[i], y[i], 15, 15);
    }
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            drawornot = 0;
            if (i != setupnumber - 1 && j != setupnumber - 1 && setup == 1) {
                drawornot = 1;
            }
            if (drawornot == 0) {
                if (adjacencyMatrix[j][i] != 0) {
                    if (j == i) {
                        if (x[i] <= xmid) {
                            ellipse(x[i] - 15, y[i], 0, 360, 20, 15);
                        } else {
                            ellipse(x[i] + 15, y[i], 0, 360, 20, 15);
                        }
                    } else {
                        setcolor(graphcolor[1]);
                        line(x[i], y[i], x[j], y[j]);
                        arrowy = abs((y[j] - y[i]) / 6);
                        arrowx = abs((x[j] - x[i]) / 6);
                        if (y[i] > y[j]) {
                            arrowy -= y[i];
                        } else {
                            arrowy += y[i];
                        }
                        if (x[i] > x[j]) {
                            arrowx -= x[i];
                        } else {
                            arrowx += x[i];
                        }
                        arrowy = abs(arrowy);
                        arrowx = abs(arrowx);
                        if (x[j] - x[i] != 0) {
                            tg = atan(-(y[j] - y[i]) / (x[j] - x[i])) * 180 / M_PI;
                        } else {
                            if (y[i] < arrowy) {
                                tg = -90;
                            } else {
                                tg = 90;
                            }
                        }
                        if (x[j] < arrowx) {
                            tg += 180;
                        }
                        setcolor(graphcolor[2]);
                        if (tg < 180) {
                            ellipse(arrowx, arrowy, tg + 90, tg + 270, 4, 4);
                        } else {
                            ellipse(arrowx, arrowy, tg - 270, tg - 90, 4, 4);
                        }
                    }
                }
            }
        }
    }
    setcolor(graphcolor[3]);
    settextstyle(0, 0, 2);
    for (i = 0; i < numVertices; i++) {
        sprintf(numbah, "%d", i + 1);
        len = strlen(numbah);
        outtextxy(x[i] - 7 * len, y[i] - 7, numbah);
    }
    getch();
    closegraph();
}

//---------------------------------------------------------
//---------------------------------------------------------
int main() {
    int menu[4];                          // For menu proper work
    int menusave[2];                      // =-=-=-=-=-=-=
    int temp[2];                          // For assign
    int grnum = 0;                          // =-=-=-=-=-=-=
    int i = 0;                              // For counting
    int ammount = 0;                        // Ammount of graphs
    int loadornot = 0;                      // For save/load purposes
    char *filename;                       // =-=-=-=-=-=-=-=
    clock_t start;                        // For clock purposes
    start = clock();
    window(1, 1, 160, 50);
    std::ifstream options("GRAPHOPT.txt");
    if (!options) {
        std::cout << "Cant open file" << std::endl;
        getch();
    }
    options.ignore(99, 'A');
    options >> temp[0];
    textbackground(temp[0]);
    options.ignore(99, 'B');
    options >> temp[0];
    textcolor(temp[0]);
    options.close();
    lowvideo();
    for (i = 0; i < 4; i++) {
        menu[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        menusave[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        temp[i] = 0;
    }
    system("clear");
    for (i = 0; i > 3 || i < 1;) {
        displayMenu(0);
        i = testInput();
        switch (i) {
            case 1: {
                system("clear");
                std::cout << "Creating new Graph cat" << std::endl << "Graphs inside?" << std::endl;
                ammount = testInput();
            }
                break;
            case 2: {
                loadornot = 1;
            }
                break;
            case 3: {
                exitProgram(start);
            }
            default: {
                std::cout << "Wrong value, reenter plz" << std::endl;
                displayMenu(0);
                i = testInput();
            }
        }
    }
    if (loadornot == 1) {
        system("clear");
        searchFile();
        std::cout << "Enter Name of file to load" << std::endl;
        std::cin >> filename;
        std::ifstream in(filename);
        if (!in) {
            std::cout << "Cant open file" << std::endl;
            exit(EXIT_FAILURE);
        }
        in >> ammount;
    }
    Graph *dunno = new Graph[ammount];
    if (loadornot == 1) {
        std::ifstream in(filename);
        if (!in) {
            std::cout << "Cant open file" << std::endl;
            exit(EXIT_FAILURE);
        }
        in >> ammount;
        for (i = 0; i < ammount; i++) {
            dunno[i].load(in);
        }
        in.close();
    }
    system("clear");
    displayMenu(1);
    menu[0] = testInput();
    for (;;) {
        menusave[0] = 0;
        system("clear");
        switch (menu[0]) {
//---------------------------------------------------------
//---------------------------------------------------------
            case 1:                             // Edit
            {
                system("clear");
                if (menusave[1] == 0) {
                    displayMenu(2);
                    menu[1] = testInput();
                }
                menusave[1] = 0;
                menusave[0] = 1;
                switch (menu[1]) {
                    case 1:                           // Add vertex
                    {
                        system("clear");
                        std::cout << "Adding Vertex" << std::endl << std::endl;
                        std::cout << "To witch Graph?" << std::endl;
                        grnum = testInput();
                        dunno[grnum - 1].addVertex();
                    }
                        break;
                    case 2:                           // Add rib
                    {
                        system("clear");
                        std::cout << "Adding rib" << std::endl << std::endl;
                        std::cout << "To witch Graph?" << std::endl;
                        grnum = testInput();
                        std::cout << "Enter from what vertex it starts" << std::endl;
                        temp[0] = testInput();
                        std::cout << "Enter at what vertex it ends" << std::endl;
                        temp[1] = testInput();
                        dunno[grnum - 1].addEdge(temp[0], temp[1]);
                    }
                        break;
                    case 3:                           // Remove vertex
                    {
                        system("clear");
                        std::cout << "Removing Vertex" << std::endl << std::endl;
                        std::cout << "From witch Graph?" << std::endl;
                        grnum = testInput();
                        std::cout << "Enter vertex that u want to remove" << std::endl;
                        temp[0] = testInput();
                        dunno[grnum - 1].removeVertex(temp[0]);
                    }
                        break;
                    case 4:                           // Remove rib
                    {
                        system("clear");
                        std::cout << "Removing rib" << std::endl << std::endl;
                        std::cout << "From witch Graph?" << std::endl;
                        grnum = testInput();
                        std::cout << "Enter from what vertex it starts" << std::endl;
                        temp[0] = testInput();
                        std::cout << "Enter at what vertex it ends" << std::endl;
                        temp[1] = testInput();
                        dunno[grnum - 1].removeEdge(temp[0], temp[1]);
                    }
                    case 5:                           // return
                    {
                        menusave[0] = 0;
                    }
                        break;
                    default: {
                        std::cout << "Bug in menueditshow" << std::endl;
                    }
                }
            }
                break;
//---------------------------------------------------------
//---------------------------------------------------------
            case 2:                             // sort
            {
                menusave[0] = 1;
                system("clear");
                displayMenu(4);
                menu[1] = testInput();
                switch (menu[1]) {
                    case 1:                           // sort by lastname
                    {

                    }
                        break;
                    case 2:                           // sort by studnumb
                    {

                    }
                        break;
                    case 3:                           // sort by points
                    {

                    }
                        break;
                    case 4:                           // return
                    {
                        menusave[0] = 0;
                    }
                        break;
                    default: {
                        std::cout << "Bug in menusortshow" << std::endl;
                    }
                }
            }
                break;
//---------------------------------------------------------
//---------------------------------------------------------
            case 3:                             // Display
            {
                system("clear");
                displayMenu(5);
                menu[2] = testInput();
                menusave[0] = 3;
                switch (menu[2]) {
                    case 1:                           // Display one Graph
                    {
                        system("clear");
                        std::cout << "Display whole Graph" << std::endl << std::endl;
                        std::cout << "Witch Graph u want to show?" << std::endl;
                        grnum = testInput();
                        dunno[grnum - 1].display(0, 0);
                    }
                        break;
                    case 2:                           // Display Vertex with all ribs
                    {
                        system("clear");
                        std::cout << "Display Vertex with all ribs" << std::endl << std::endl;
                        std::cout << "Witch Graph u want to show?" << std::endl;
                        grnum = testInput();
                        std::cout << "Witch Vertex?" << std::endl;
                        temp[0] = testInput();
                        dunno[grnum - 1].display(1, temp[0]);
                    }
                        break;
                    case 3:                           // Info about Graph
                    {
                        system("clear");
                        std::cout << "Display whole info about Graph" << std::endl;
                        std::cout << "Witch Graph info u want?" << std::endl;
                        grnum = testInput();
                        dunno[grnum - 1].info();
                        getch();
                    }
                        break;
                    case 4:                           // Return
                    {
                        menusave[0] = 0;
                    }
                        break;
                    default: {
                        std::cout << "Bug in menusortshow" << std::endl;
                    }
                }
            }
                break;
//---------------------------------------------------------
//---------------------------------------------------------
            case 4:                             // Options
            {
                menusave[0] = 1;
                system("clear");
                displayMenu(6);
                menu[1] = testInput();
                switch (menu[1]) {
                    case 1:                           // BackGround color
                    {
                        system("clear");
                        std::cout << "Set new background color" << std::endl << std::endl;
                        temp[0] = setColor('A');
                        textbackground(temp[0]);
                    }
                        break;
                    case 2: {
                        system("clear");                        // Text color
                        std::cout << "Set new text color" << std::endl << std::endl;
                        temp[0] = setColor('B');
                        textcolor(temp[0]);
                    }
                        break;
                    case 3: {
                        system("clear");                        // Vertexes color
                        std::cout << "Set new vertexes color" << std::endl << std::endl;
                        temp[0] = setColor('C');
                    }
                        break;
                    case 4: {
                        system("clear");                        // Lines color
                        std::cout << "Set new lines color" << std::endl << std::endl;
                        temp[0] = setColor('D');
                    }
                        break;
                    case 5: {
                        system("clear");                        // Arrows color
                        std::cout << "Set new arrows color" << std::endl << std::endl;
                        temp[0] = setColor('E');
                    }
                        break;
                    case 6: {
                        system("clear");                        // Numbers color
                        std::cout << "Set new numbers color" << std::endl << std::endl;
                        temp[0] = setColor('F');
                    }
                        break;
                    case 7:                           // Return
                    {
                        menusave[0] = 0;
                    }
                        break;
                    default: {

                    }
                }
            }
                break;
//---------------------------------------------------------
//---------------------------------------------------------
            case 5:                             // Save
            {
                char *filename;
                std::cout << "Enter name of file" << std::endl;
                std::cin >> filename;
                std::ofstream out(filename);
                if (!out) {
                    std::cout << "Cant open file" << std::endl;
                    getch();
                }
                out << ammount << " ";
                for (i = 0; i < ammount; i++) {
                    dunno[i].save(out);
                }
                out.close();
            }
                break;
//---------------------------------------------------------
//---------------------------------------------------------
            case 6:                             // Exit
            {
                exitProgram(start);
            }
                break;
            default: {
                std::cout << "Bug in display menu" << std::endl;
            }
        }
        system("clear");
        if (menusave[0] == 0) {
            displayMenu(1);
            menu[0] = testInput();
        }
    }
}

//---------------------------------------------------------
//---------------------------------------------------------
void displayMenu(int an) {
    if (an == 0) {
    std::cout << "   Init" << std::endl << std::endl;
    std::cout << "1. New" << std::endl;
    std::cout << "2. Load" << std::endl;
    std::cout << "3. Exit" << std::endl;
    } else if (an == 1) {
    std::cout << "   Menu" << std::endl << std::endl;
    std::cout << "1. Edit" << std::endl;
    std::cout << "2. ....." << std::endl;
    std::cout << "3. Display" << std::endl;
    std::cout << "4. Options" << std::endl;
    std::cout << "5. Save" << std::endl;
    std::cout << "6. Exit" << std::endl;
    } else if (an == 2) {
    std::cout << "   Edit" << std::endl << std::endl;
    std::cout << "1. Add vertex" << std::endl;
    std::cout << "2. Add rib" << std::endl;
    std::cout << "3. Remove vertex" << std::endl;
    std::cout << "4. Remove rib" << std::endl;
    std::cout << "5. Return" << std::endl;
    } else if (an == 3) {
    std::cout << "   ....." << std::endl << std::endl;
    std::cout << "1. ....." << std::endl;
    std::cout << "2. ....." << std::endl;
    std::cout << "3. ....." << std::endl;
    std::cout << "4. ....." << std::endl;
    std::cout << "5. Return" << std::endl;
    } else if (an == 4) {
    std::cout << "   ....." << std::endl << std::endl;
    std::cout << "1. ....." << std::endl;
    std::cout << "2. ....." << std::endl;
    std::cout << "3. ....." << std::endl;
    std::cout << "4. Return" << std::endl;
    } else if (an == 5) {
    std::cout << "   Display:" << std::endl << std::endl;
    std::cout << "1. Whole Graph" << std::endl;
    std::cout << "2. One vertexs ribs" << std::endl;
    std::cout << "3. Info about Graph" << std::endl;
    std::cout << "4. Return" << std::endl;
    } else if (an == 6) {
    std::cout << "   Options:" << std::endl << std::endl;
    std::cout << "1. Background color" << std::endl;
    std::cout << "2. Text color" << std::endl;
    std::cout << "3. Vertexes color" << std::endl;
    std::cout << "4. Lines color" << std::endl;
    std::cout << "5. Arrows color" << std::endl;
    std::cout << "6. Numbers color" << std::endl;
    std::cout << "7. Return" << std::endl;
    }
}

//---------------------------------------------------------
//---------------------------------------------------------
int charToInt(char *p) {
    int numb = 0;
    while (*p) {
        (numb *= 10) += *p++ - '0';
    }
    return numb;
}

//---------------------------------------------------------
//---------------------------------------------------------
int testInput() {
    char *test = NULL;
    int etest = 0;
    std::cin >> test;
    for (; isdigit(*test) == 0;) {
        std::cout << "You must enter Number" << std::endl;
        std::cin >> test;
    }
    etest = charToInt(test);
    return etest;
}

//---------------------------------------------------------
//---------------------------------------------------------
void exitProgram(clock_t start) {
    clock_t end;
    end = clock();
    int countfornumber = 0;
    int countfordots = 0;
    for (countfornumber = 3; countfornumber > 0; countfornumber--) {
        system("clear");
        std::cout << "U worked in programm " << (end - start) / CLK_TCK << " seconds" << std::endl;
        std::cout << "Exiting Program in " << countfornumber;
        for (countfordots = 0; countfordots < 5; countfordots++) {
            delay(200);
            std::cout << ".";
        }
    }
    exit(0);
}

//---------------------------------------------------------
//---------------------------------------------------------
void searchFile() {
    struct ffblk ffblk;
    int done;
    std::cout << "All txt files inside of directory" << std::endl;
    done = findfirst("*.txt", &ffblk, 0);
    while (!done) {
        std::cout << " " << ffblk.ff_name << std::endl;
        done = findnext(&ffblk);
    }
    std::cout << std::endl;
}

//---------------------------------------------------------
//---------------------------------------------------------
int setColor(int pos) {
    int color;
    std::cout << "Choose Number of color" << std::endl << std::endl;
    std::cout << "BLACK          0" << std::endl;
    std::cout << "BLUE           1" << std::endl;
    std::cout << "GREEN          2" << std::endl;
    std::cout << "CYAN           3" << std::endl;
    std::cout << "RED            4" << std::endl;
    std::cout << "MAGENTA        5" << std::endl;
    std::cout << "BROWN          6" << std::endl;
    std::cout << "LIGHTGRAY      7" << std::endl;
    std::cout << "DARKGRAY       8" << std::endl;
    std::cout << "LIGHTBLUE      9" << std::endl;
    std::cout << "LIGHTGREEN    10" << std::endl;
    std::cout << "LIGHTCYAN     11" << std::endl;
    std::cout << "LIGHTRED      12" << std::endl;
    std::cout << "LIGHTMAGENTA  13" << std::endl;
    std::cout << "YELLOW        14" << std::endl;
    std::cout << "WHITE         15" << std::endl;
    color = testInput();
    for (; color < 0 || color > 15;) {
        std::cout << "Number must be between 0 and 15" << std::endl;
        color = testInput();
    }
    std::fstream col("GRAPHOPT.txt", std::ios::in | std::ios::out);
    if (!col) {
        std::cout << "Cant open file" << std::endl;
        getch();
    }
    col.ignore(99, pos);
    col << color;
    if (color < 10) {
        col << " ";
    }
    col.close();
    return color;
}
