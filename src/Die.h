class Die 
{
	private:
		int eyes;
		bool unused;
	public:
		Die();
		Die(int fixedEyes);
		int getEyes() const;
		bool isUnused() const;
		void roll();
		void use();
};
