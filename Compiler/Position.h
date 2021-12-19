#pragma once

struct position {
	int lineNumber, charNumber;

	bool operator<(const position&) const;

	bool operator>(const position&) const;

	bool operator<=(const position&) const;

	bool operator>=(const position&) const;

	bool operator==(const position&) const;

	bool operator!=(const position&) const;
};



