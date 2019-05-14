//Sasha Ohayon (20709137) & Joshua Fernandes (20765616)
//MTE140 - 101

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

using namespace std;

class Artwork {
protected:
	string artistName;
	string title;
	unsigned int year;

public:
	Artwork() : year(0), title(""), artistName("") {
	}

	Artwork(string artistName0, string title0, unsigned int year0) {
		artistName = artistName0;
		title = title0;
		year = year0;
	}

	string getArtist() {
		return artistName;
	}

	string getTitle() {
		return title;
	}

	unsigned int getYear() {
		return year;
	}

	friend bool operator==(const Artwork& art0, const Artwork& art1) ;

};

class SoldArtwork : public Artwork {
	string customerName;
	string customerAddress;
	double saleAmt;

public:
	SoldArtwork() {
		Artwork::year = 0;
		Artwork::title = "";
		Artwork::artistName = "";
		customerName = "";
		customerAddress = "";
		saleAmt = 0;
	}

	SoldArtwork(string customerName0, string customerAddress0, double saleAmt0, Artwork art0) :
		customerName(customerName0), customerAddress(customerAddress0), saleAmt(saleAmt0), Artwork(art0) {}

	string getCustomer() {
		return customerName;
	}

	string getCustomerAddress() {
		return customerAddress;
	}

	double getSaleAmt() {
		return saleAmt;
	}

	friend bool operator==(const SoldArtwork& sart0, const SoldArtwork& sart1);
};


class ArtCollection {
	vector<Artwork> artColl;
	vector<SoldArtwork> sartColl;

public:

	vector<Artwork> getArt() const {
		return artColl;
	}

	vector<SoldArtwork> getSoldArt() const {
		return sartColl;
	}

	bool insert_artwork(const Artwork& artwork_info) {
		for (int i = 0; i < artColl.size(); i++) {
			if (artwork_info == artColl[i])
				return false;
		}
		artColl.push_back(artwork_info);
		return true;
	}

	bool sell_artwork(const SoldArtwork& artwork_info) {
		bool flag = false;
		for (int i = 0; i < artColl.size(); i++) {
			if (static_cast<Artwork>(artwork_info) == artColl[i]) {
				artColl.erase(artColl.begin() + i);
				flag = true;
				break;
			}
		}

		if (flag)
			sartColl.push_back(artwork_info);

		return flag;
	}

	bool operator==(const ArtCollection& artCollection) const {

		if (artColl.size() != artCollection.artColl.size())
			return false;

		bool flag = false;

		for (int i = 0; i < artColl.size(); i++) {
			for (int j = 0; j < artCollection.artColl.size(); j++) {

				if (artColl[i] == artCollection.artColl[j]) {
					flag = true;
				}
			}

			if (!flag) {
				return false;
			}
			flag = false;
		}

		if (sartColl.size() != artCollection.sartColl.size())
			return false;

		for (int i = 0; i < sartColl.size(); i++) {
			for (int j = 0; j < artCollection.sartColl.size(); j++) {

				if (sartColl[i] == artCollection.sartColl[j])
					flag = true;
			}

			if (!flag) {
				return false;
			}
			flag = false;
		}

		return true;
	}

	friend ArtCollection operator+(const ArtCollection& artColl0, const ArtCollection& artColl1);

};

bool operator==(const Artwork& art0, const Artwork& art1)  {
	return (art1.artistName == art0.artistName && art1.title == art0.title && art1.year == art0.year);
}

bool operator==(const SoldArtwork& art0, const SoldArtwork& art1) {
	return (art1.artistName == art0.artistName && art1.title == art0.title && art1.year == art0.year && art1.customerName == art0.customerName && art1.customerAddress == art0.customerAddress && art1.saleAmt == art0.saleAmt);
}

ArtCollection operator+(const ArtCollection& artColl0, const ArtCollection& artColl1) {
	ArtCollection finalColl;
	bool flag = false;

	for (int i = 0; i < artColl0.artColl.size(); i++) {
		finalColl.artColl.push_back(artColl0.artColl[i]);
	}

	for (int i = 0; i < artColl0.sartColl.size(); i++) {
		finalColl.sartColl.push_back(artColl0.sartColl[i]);
	}

	for (int i = 0; i < artColl1.artColl.size(); i++) {
		for (int j = 0; j < finalColl.artColl.size(); j++) {
			if (finalColl.artColl[j] == artColl1.artColl[i]) {
				flag = true;
				break;
			}
		}

		if (!flag)
			finalColl.artColl.push_back(artColl1.artColl[i]);

		flag = false;
	}

	for (int i = 0; i < artColl1.sartColl.size(); i++) {
		finalColl.sartColl.push_back(artColl1.sartColl[i]);
	}

	return finalColl;
}

bool test_insert_artwork() {
	ArtCollection artCollection;
	artCollection.insert_artwork(Artwork("Great Artist", "Great Art", 2019));
	artCollection.insert_artwork(Artwork("Bad Artist", "Bad Art", 2019));

	if (artCollection.getArt().size() == 0) {
		cout << "Test 1 - test_insert_artwork: Fail\n\n";
		return false;
	}

	artCollection.insert_artwork(Artwork("Great Artist", "Great Art", 2019));

	if (artCollection.getArt().size() == 3) {
		cout << "Test 1 - test_insert_artwork: Fail\n\n";
		return false;
	}
	cout << "Test 1 - test_insert_artwork: Pass\n\n";

	return true;
}

bool test_sell_artwork() {
	ArtCollection artCollection;
	Artwork goodArt("Great Artist", "Great Art", 2019);
	artCollection.insert_artwork(goodArt);
	artCollection.insert_artwork(Artwork("Bad Artist", "Bad Art", 2019));

	artCollection.sell_artwork(SoldArtwork("Guy Who Bought", "1 Place Lane", 1000, goodArt));

	if (artCollection.getArt().size() != 1 || artCollection.getSoldArt().size() != 1) {
		cout << "Test 2 - test_sell_artwork: Pass\n\n";
		return false;
	}

	cout << "Test 2 - test_sell_artwork: Pass\n\n";

	return true;
}

bool test_compare_collections() {
	ArtCollection artCollection;
	Artwork goodArt("Great Artist", "Great Art", 2019);
	artCollection.insert_artwork(goodArt);
	artCollection.insert_artwork(Artwork("Bad Artist", "Bad Art", 2018));
	artCollection.insert_artwork(Artwork("Artist", "Art", 2017));
	artCollection.sell_artwork(SoldArtwork("Guy Who Bought", "1 Place Lane", 1000, goodArt));

	ArtCollection artCollection2;
	artCollection2.insert_artwork(goodArt);
	artCollection2.insert_artwork(Artwork("Bad Artist", "Bad Art", 2018));
	artCollection2.insert_artwork(Artwork("Artist", "Art", 2017));
	artCollection2.sell_artwork(SoldArtwork("Guy Who Bought", "1 Place Lane", 1000, goodArt));

	if (!(artCollection == artCollection2)) {
		cout << "Test 3 - test_compare_collections: Fail\n\n";
		return false;
	}

	artCollection2.insert_artwork(Artwork("Artist", "Broken Art", 2016));

	if (artCollection == artCollection2) {
		cout << "Test 3 - test_compare_collections: Fail\n\n";
		return false;
	}

	cout << "Test 3 - test_compare_collections: Pass\n\n";
	return true;
}

bool test_add_collections() {
	ArtCollection artCollection;
	Artwork goodArt("Great Artist", "Great Art", 2019);
	artCollection.insert_artwork(goodArt);
	artCollection.insert_artwork(Artwork("Bad Artist", "Bad Art", 2018));
	artCollection.insert_artwork(Artwork("Artist", "Art", 2017));
	artCollection.sell_artwork(SoldArtwork("Guy Who Bought", "1 Place Lane", 1000, goodArt));
	artCollection.insert_artwork(goodArt);

	ArtCollection artCollection2;
	artCollection2.insert_artwork(goodArt);
	artCollection2.insert_artwork(Artwork("Artist", "Good Art", 2017));
	artCollection2.insert_artwork(Artwork("Artist", "Mediocre Art", 2017));
	artCollection2.sell_artwork(SoldArtwork("Guy", "1 Blvd", 1000, goodArt));
	artCollection2.insert_artwork(goodArt);

	ArtCollection artCollection3 = artCollection + artCollection2;

	if (artCollection3.getArt().size() != 5) {
		cout << "Test 4 - test_add_collections: Fail\n\n";
		return false;
	}

	if (artCollection3.getSoldArt().size() != 2) {
		cout << "Test 4 - test_add_collections: Fail\n\n";
		return false;
	}

	cout << "Test 4 - test_add_collections: Pass\n\n";

	return true;
}

int main() {
	if (test_insert_artwork() && test_sell_artwork() && test_compare_collections() && test_add_collections())
		cout << "All of the tests passed\n\n";

	system("PAUSE");
	return 0;
}


/*OUPTUT
Test 1 - test_insert_artwork: Pass

Test 2 - test_sell_artwork: Pass

Test 3 - test_compare_collections: Pass

Test 4 - test_add_collections: Pass

All of the tests passed

Press any key to continue . . .
*/
