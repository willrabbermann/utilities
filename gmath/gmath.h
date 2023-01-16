#ifndef GMATH_H
#define GMATH_H

#define GMATH_DEBUG

int iclamp(int target, int max, int min)
{
	if (target > max)
		return max;
	if (target < min)
		return min;
	else return target;
}

typedef struct {
	float x, y, z, w;
} vec4f;

vec4f *newvec4f(float x, float y, float z, float w)
// Initialize a new vec4f
{
	vec4f *new = malloc(sizeof(vec4f));
	new->x = x;
	new->y = y;
	new->z = z;
	new->w = w;
		
	return new;
}

void transform(vec4f *left, vec4f *right)
// transform left by right
{
	left->x = left->x + right->x;
	left->y = left->y + right->y;
	left->z = left->z + right->z;
	left->w = left->w + right->w;
}

void scale(vec4f *left, float right)
// scale left by right
{
	left->x = left->x * right;
	left->y = left->y * right;
	left->z = left->z * right;
	left->w = left->w * right;
}

void printvec4f(vec4f *v)
{
	printf("{ %f, %f, %f, %f }\n", v->x, v->y, v->z, v->w);
}

// Linked List of vec4f
typedef struct node {
	struct node *next;
	struct node *prev;
	vec4f *position;
} node;

node *newnode(vec4f *v, node *n)
// Add new node to the end of the list, 
// regardless of n's position in the list.
// Start a new list with n = NULL.
{
	node *new = malloc(sizeof(node));
	if (n)
	{
		node *p = n;
		while(p->next)
			p = p->next;
		new->position = v;
		new->next = NULL;
		new->prev = p;
		p->next = new;
		return new;
	}
	else
	{
		new->position = v;
		new->next = NULL;
		new->prev = NULL;
		return new;
	}
}

void freenode(node *n)
// Free any node from the list.
{
	printf("\nFreeing node: ");
	printvec4f(n->position);
	
	if (n->prev && n->next)
	{
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	else if (!n->prev && n->next)
		n->next->prev = NULL;
	else if (!n->next && n->prev)
		n->prev->next = NULL;
	free(n);
}

void printnodes(node *n)
{
	printf("Start\n|\n---> ");
	node *p = n;
	while(p->prev)
		p = p->prev;
	while(1)
	{
		printf("\t[\n\t\tnext = %p,\n\t\tprev = %p,\n\t\tposition = { %f, %f, %f, %f }\n", (void *)p->next, 
				(void *)p->prev, p->position->x, p->position->y, p->position->z, p->position->w );
		
		if(p->next)
		{
			printf("------\t]\n|\n|\n---> ");
			p = p->next;
		}
		else
		{	
			printf("\t]\n");
			break;
		}
	}
}

#ifdef GMATH_DEBUG
void GMATH_Tests()
{
	printf("sizeof(int) = %ld bytes\n", sizeof(int)); 		// 4 bytes
	printf("sizeof(float) = %ld bytes\n", sizeof(float)); 	// 4 bytes
	printf("sizeof(double) = %ld bytes\n", sizeof(double));	// 8 bytes
	printf("sizeof(void *) = %ld bytes\n", sizeof(void *));	// 8 bytes

	vec4f *v = newvec4f(0.0f, 1.5f, 1.0f, 1.0f);
	printf("Initial vec4f\nv = ");
	printvec4f(v);
	
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("\nb = ");
	printvec4f(b);
	
	transform(v, b);

	free(b);
	printf("transform(v, b)\nv = ");
	printvec4f(v);

	float c = 2.0f;	
	printf("\nscale(v, %f)\nv = ", c);
	scale(v, c);
	printvec4f(v);

	printf("\n"); 
	
	// Create an array of pointers (8 bytes * size)
	const int size = 8;
	node *nodeArray[size];
	printf("\nsizeof(nodeArray) = %ld bytes\n", sizeof(nodeArray));
	
	// Init to null
	for (int i = 0; i < size; i++)
		nodeArray[i] = 0; 


	// Randomly generate nodes
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		if (i)
			nodeArray[i] = 
				newnode(newvec4f(sin(rand()), sin(rand()), sin(rand()), sin(rand())), 
						nodeArray[i-1]);
		else
			nodeArray[i] = 
				newnode(newvec4f(sin(rand()), sin(rand()), sin(rand()), sin(rand())), 
						0);
	}
	
	printnodes(nodeArray[0]); 
	
	// Remove some nodes
	freenode(nodeArray[1]);
	nodeArray[1] = 0;
	freenode(nodeArray[size-1]);
	nodeArray[size-1] = 0;

	printnodes(nodeArray[size-2]); 
	
	// Free all the nodes
	for (int i = 0; i < size; i++)
	{
		if (nodeArray[i])
			freenode(nodeArray[i]);
	}
}
#endif
#endif
