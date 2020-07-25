class Die 
{
	private:
		int eyes;
		bool unused;
	public:
		Die(int fixedEyes);
		int getEyes();
		bool isUnused();
		void roll();
		void use();
};
