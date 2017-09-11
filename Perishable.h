#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__

#include "NonPerishable.h"
#include "Date.h"

namespace ict {

	class Perishable : public NonPerishable {


	private:
		Date m_expiry; //date-only

	protected:
		char signature() const;

	public:
		Perishable();

		std::fstream& save(std::fstream& file) const;
		std::fstream& load(std::fstream& file);
		ostream& write(ostream& ostr, bool linear) const;
		std::istream& read(std::istream& istr);

	};
}





#endif
