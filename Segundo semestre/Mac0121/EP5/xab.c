typedef struct pathi_t {
    PNode* head;
} PathI;


typedef struct protopath_t {
    int value, *tops;
    Pos **stacks;
} PPath;


/*Retirar*//*
void printBo(BTile **board, int m, int n) {
int i, j;
for (i = 0; i < m; i++){
for (j = 0; j < n; j++){
printf("========================================\n");
printf("lin = %d\n", board[i][j].lin);
printf("col = %d\n", board[i][j].col);
printf("color = %c\n", board[i][j].color);
if (board[i][j].Neigh[0]) {
printf("Neigh[0] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[0], board[i][j].Neigh[0]->lin, board[i][j].Neigh[0]->col);
}
else {
printf("Neigh[0] = NULL\n");
}
printf("Weight[0] = [0]%d/[1]%d\n", board[i][j].weights[0][0], board[i][j].weights[0][1]);
if (board[i][j].Neigh[1]) {
printf("Neigh[1] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[1], board[i][j].Neigh[1]->lin, board[i][j].Neigh[1]->col);
}
else {
printf("Neigh[1] = NULL\n");
}
printf("Weight[1] = [0]%d/[1]%d\n", board[i][j].weights[1][0], board[i][j].weights[1][1]);
if (board[i][j].Neigh[2]) {
printf("Neigh[2] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[2], board[i][j].Neigh[2]->lin, board[i][j].Neigh[2]->col);
}
else {
printf("Neigh[2] = NULL\n");
}
printf("Weight[2] = [0]%d/[1]%d\n", board[i][j].weights[2][0], board[i][j].weights[2][1]);
if (board[i][j].Neigh[3]) {
printf("Neigh[3] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[3], board[i][j].Neigh[3]->lin, board[i][j].Neigh[3]->col);
}
else {
printf("Neigh[3] = NULL\n");
}
printf("Weight[3] = [0]%d/[1]%d\n", board[i][j].weights[3][0], board[i][j].weights[3][1]);
if (board[i][j].Neigh[4]){
printf("Neigh[4] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[4], board[i][j].Neigh[4]->lin, board[i][j].Neigh[4]->col);
}
else {
printf("Neigh[4] = NULL\n");
}
printf("Weight[4] = [0]%d/[1]%d\n", board[i][j].weights[4][0], board[i][j].weights[4][1]);
if (board[i][j].Neigh[5]) {
printf("Neigh[5] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[5], board[i][j].Neigh[5]->lin, board[i][j].Neigh[5]->col);
}
else {
printf("Neigh[5] = NULL\n");
}
printf("Weight[5] = [0]%d/[1]%d\n", board[i][j].weights[5][0], board[i][j].weights[5][1]);
}
}
}
*/

/*
PPath *PPathCreate () {
    const char errmsg[] = "O protótipo de caminho não pode ser alocado\n";
    PPath *ret;
    ret = emalloc(sizeof(PPath), errmsg);
    ret->stacks = emalloc(2*sizeof(Pos*), errmsg);
    ret->stacks[0] = emalloc(20*sizeof(Pos), errmsg);
    ret->stacks[1] = emalloc(20*sizeof(Pos), errmsg);
    ret->tops = emalloc(2*sizeof(int*), errmsg);
    ret->tops[0] = 0;
    ret->tops[1] = 0;
    ret->value = 0;
    return ret;
}

void PPathDestroy (PPath *path) {
    free(path->stacks[0]);
    free(path->stacks[1]);
    free(path->stacks);
    free(path->tops);
    free(path);
}

void PPathPush (PPath *path, int stack, int lin, int col, char color) {
    int prevColor;
    printf("Adding (%d:%d) %c to stack %d\n", lin, col, color, stack);
    path->stacks[stack][path->tops[stack]].lin = lin;
    path->stacks[stack][path->tops[stack]].col = col;
    path->stacks[stack][path->tops[stack]].color = color;
    if (path->tops[stack] != 0) {
        prevColor = path->stacks[stack][(path->tops[stack])-1].color;
        if (color == '-' && prevColor == '-')
            path->value += 4;
        else if (color != prevColor)
            path->value += 2;
    }
    (path->tops[stack])++;
}

Pos PPathPop (PPath *path, int stack) {
    int prevColor, color;
    if (path->tops[stack] > 1) {
        color = path->stacks[stack][(path->tops[stack])-1].color;
        prevColor = path->stacks[stack][(path->tops[stack])-2].color;
        if (color == '-' && prevColor == '-')
            path->value -= 4;
        else if (color != prevColor)
            path->value -= 2;
    }
    (path->tops[stack])--;
    printf("Removing (%d:%d)\n", path->stacks[stack][path->tops[stack]].lin, path->stacks[stack][path->tops[stack]].col);
    return path->stacks[stack][path->tops[stack]];
}

int PPathIsFull (PPath *path) {
    if (path->tops[0] == 20 || path->tops[1] == 20)
        return 1;
    return 0;
}
*/

/*
PathI *PPtoP (PPath *ppath) {
    const char errmsg[] = "O nó de lista ligada não pode ser alocado\n";
    int i;
    PathI *ret;
    PNode *auxNode;
    ret = emalloc(sizeof(PathI), errmsg);
    ret->head = NULL;
    for (i = ppath->tops[1] - 1; i > 0; i--) {
        auxNode = emalloc(sizeof(PNode), errmsg);
        auxNode->lin = ppath->stacks[1][i].lin;
        auxNode->col = ppath->stacks[1][i].col;
        auxNode->color = ppath->stacks[1][i].color;
        auxNode->next = ret->head;
        ret->head = auxNode;
    }
    for (i = 0; i < ppath->tops[0]; i++) {
        auxNode = emalloc(sizeof(PNode), errmsg);
        auxNode->lin = ppath->stacks[0][i].lin;
        auxNode->col = ppath->stacks[0][i].col;
        auxNode->color = ppath->stacks[0][i].color;
        auxNode->next = ret->head;
        ret->head = auxNode;
    }
    return ret;
}
*/
/*Cria um vetor de tamanho "tam" e retorna um ponteiro para ele*/
/*Colocar emalloc*/

/*
void PathDestroy (PathI *path) {
    PNode *ptr, *ptrAux;
    ptr = path->head;
    while (ptr != NULL) {
        ptrAux = ptr;
        ptr = ptr->next;
        free(ptrAux);
    }
    free(path);
}*/

int partialFindPath (BTile **board, PPath *path, int **used, int lin, int col, char color, int dir, int par) {
    char thiscolor = board[lin][col].color;
    char otcolor = (color == 'b')? 'p' : 'b';
    int i, linN, colN, *priority, res = 0;
    if (PPathIsFull(path)) {
        /*printf("Path is full, returning 0\n");*/
        return 0;
    }
    if (used[lin][col]) {
        /*printf("%d:%d already used\n", lin, col);*/
        return 0;
    }
    /*printf("Marking %d:%d as used\n", lin, col);*/
    used[lin][col] = 1;
    imprimeMatriz(used, 14, 14);
    if (thiscolor != '-' && thiscolor != color) {
        /*printf("Tile has oposit color, returning 0\n");*/
        return 0;
    }
    PPathPush(path, dir, lin, col, thiscolor);
    if (color == 'b') {
        if (dir == 0 && lin == 0) {
            /*printf("Position is a goal\n");*/
            return 1;
        }
        if (dir == 1 && lin == N-1) {
            /*printf("Position is a goal\n");*/
            return 1;
        }
    }
    else {
        if (dir == 0 && col == 0) {
            /*printf("Position is a goal\n");*/
            return 1;
        }
        if (dir == 1 && col == N-1) {
            /*printf("Position is a goal\n");*/
            return 1;
        }
    }
    priority = getPriority(board, lin, col, color, dir, par);
    /*imprimeVetor(priority, 6);*/
    for (i = 0; i < 6 && !res; i++) {
        if (board[lin][col].Neigh[priority[i]] != NULL) {
            /*if (i != 0)
                printf("%d:%d: Neighbor %d returned 0, checking neighbor %d\n", lin, col, priority[i-1], priority[i]);*/
            linN = board[lin][col].Neigh[priority[i]]->lin;
            colN = board[lin][col].Neigh[priority[i]]->col;
            res = partialFindPath(board, path, used, linN, colN, color, dir, !par);
        }
        if (board[lin][col].Neigh[i] != NULL && board[lin][col].Neigh[(i+2)%6] != NULL) {
            if (board[lin][col].Neigh[i]->color == otcolor && board[lin][col].Neigh[(i+2)%6]->color == otcolor) {
                res = 0;
                break;
            }
        }
    }
    free(priority);
    if (res != 1) {
        /*printf("%d:%d: Partial path returned 0 or -1\n", lin, col);*/
        PPathPop(path, dir);
        return res;
    }
    /*printf("%d:%d: All alright, returning 1\n", lin, col);*/
    return 1;
}

PathI *findPath (BTile **board, char color) {
    int i, j, k, l, m, ret1, ret2, cont = 0;
    PPath *ppath1, *ppath2;
    PathI *ret;
    int **used;
    ppath2 = NULL;
    used = criaMatriz(N, N);
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            if (board[i][j].color == color) {
                for (m = 0; m < 2; m++) {
                    for (k = 0; k < N; k++)
                        for (l = 0; l < N; l++)
                            used[k][l] = 0;
                    ppath1 = PPathCreate();
                    printf("Creating Protopath1\n");
                    ret1 = partialFindPath(board, ppath1, used, i, j, color, 0, m);
                    /*printf("Finding direction 0 and returning %d\n", ret1);*/
                    used[i][j] = 0;
                    ret2 = partialFindPath(board, ppath1, used, i, j, color, 1, m);
                    /*printf("Finding direction 1 and returning %d\n", ret2);*/
                    if (ret1 != 1 || ret2 != 1) {
                        /*printf("Destoying path1\n");*/
                        PPathDestroy(ppath1);
                        continue;
                    }
                    cont = 1;
                    if (ppath2 == NULL) {
                        /*printf("Transfering path1 to path2, because path2 == NULL\n");*/
                        ppath2 = ppath1;
                    }
                    else if (ppath1->value < ppath2->value) {
                        /*printf("Destroying path2\n");*/
                        /*printf("Transfering path1 to path2, because %d < %d\n", ppath1->value, ppath2->value);*/
                        PPathDestroy(ppath2);
                        ppath2 = ppath1;
                    }
                    else {
                        /*printf("Destroying path1 because %d >= %d\n", ppath1->value, ppath2->value);*/
                        PPathDestroy(ppath1);
                    }
                }
            }
        }
    if (!cont)
        ret = NULL;
    else
        ret = PPtoP(ppath2);
    freeMatriz(used, N);
    /*printf("Destoying ppath2\n");*/
    PPathDestroy(ppath2);
    return ret;
}
