class unit
{
private:
	unsigned char offence;
	unsigned char defence;
	unsigned char damage;
	unsigned char speed;
	unsigned char initiative;
	unsigned char experience;
	char *description;
public:
	unit();
	unsigned char get_offence();
	unsigned char get_defence();
	unsigned char get_damage();
	unsigned char get_speed();
	unsigned char get_initiative();
	unsigned char get_experience();
	void get_description();
}