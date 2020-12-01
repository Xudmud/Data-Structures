#include "NodePicture.h"

//Equality operator
//Check each field. If one fails, it falls out of the if and returns false.
//If all fields are equal, the object is equal, return true.
bool operator ==(const Picture& pic1, const Picture& pic2)
{
	if (pic1.name == pic2.name)
	{
		if (pic1.year == pic2.year)
		{
			if (pic1.nominations == pic2.nominations)
			{
				if (pic1.rating == pic2.rating)
				{
					if (pic1.duration == pic2.duration)
					{
						if (pic1.genre1 == pic2.genre1)
						{
							if (pic1.genre2 == pic2.genre2)
							{
								if (pic1.release == pic2.release)
								{
									if (pic1.metacritic == pic2.metacritic)
									{
										if (pic1.synopsis == pic2.synopsis)
											return(true);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return(false);
}

//Compare functions. Used with vector sort function.
bool comparePictureName(const Picture& pic1, const Picture& pic2)
{
	return(pic1.name < pic2.name);
}

bool comparePictureYear(const Picture& pic1, const Picture& pic2)
{
	return(pic1.year < pic2.year);
}

bool comparePictureNominations(const Picture& pic1, const Picture& pic2)
{
	return(pic1.nominations < pic2.nominations);
}

bool comparePictureRating(const Picture& pic1, const Picture& pic2)
{
	return(pic1.rating < pic2.rating);
}

bool comparePictureDuration(const Picture& pic1, const Picture& pic2)
{
	return(pic1.duration < pic2.duration);
}

bool comparePictureGenre1(const Picture& pic1, const Picture& pic2)
{
	return(pic1.genre1 < pic2.genre1);
}

bool comparePictureGenre2(const Picture& pic1, const Picture& pic2)
{
	return(pic1.genre2 < pic2.genre2);
}

bool comparePictureRelease(const Picture& pic1, const Picture& pic2)
{
	return(pic1.release < pic2.release);
}

bool comparePictureMetacritic(const Picture& pic1, const Picture& pic2)
{
	return(pic1.metacritic < pic2.metacritic);
}

bool comparePictureSynopsis(const Picture& pic1, const Picture& pic2)
{
	return(pic1.synopsis < pic2.synopsis);
}
