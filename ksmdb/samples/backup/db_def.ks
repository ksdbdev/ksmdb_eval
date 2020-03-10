declare database student;
class grade
{
	int4				id;
	string<50>			name;
	string<10>			classroom;
	double<0>	math;
	double<0>	Chinese;
	double<0>	english;
	unique tree<id> pkey;
	tree<name>	nameindex;
	tree<classroom>	classroom;
	tree<name,classroom> nameclassroom;
};
