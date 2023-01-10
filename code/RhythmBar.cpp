#include "RhythmBar.h"

RhythmBar::RhythmBar()
{
	m_range = 480 * 8; //range of note units to be displayed; default is two measures (8 beats)
	m_active = false;
	
	m_player = P1;
	m_color = Color::Green; //if it displays green, setting error
}

void RhythmBar::setUp(PlayerID id, Color color, int range)
{
	setPlayer(id);
	setColor(color);
	setRange(range);
	m_displayRange = 480 * 4; //default display one measure at a time
}
void RhythmBar::setPlayer(PlayerID id)
{
	m_player = id;
}
void RhythmBar::setColor(Color color)
{
	m_color = color;
}
void RhythmBar::setRange(int range)
{
	m_range = range;
}
void RhythmBar::setDisplayRange(int range)
{
	m_displayRange = range;
}
vector<RectangleShape*> RhythmBar::getRects()
{
	return m_rects;
}

void RhythmBar::setActive(bool active)
{
	if (m_active != active)
	{
		m_active = active;
		if (!m_active)
		{
			//if deactivated,
			//loop and delete current rectangle vector
		}
	}
}
//maybe use activate() instead and have it auto deactivate
//because it will always be done once the range has passed

void RhythmBar::activate(Track* track, int midiTime)
{
	if (!m_active)
	{
		m_active = true;
		m_activateTime = midiTime;
		m_lastUpdated = midiTime;
		loadNotes(track->getNotesInRange(midiTime, m_range));
	}
}
void RhythmBar::deactivate()
{
	m_active = false;
	for (size_t i = 0; i < m_rects.size(); i++)
	{
		delete m_rects.at(i);
	}
	m_rects.clear();
}
void RhythmBar::loadNotes(vector<Note*> notes)
{

	//TEST height / positioning of note rectangles with predetermined notes
	/*
	cout << "activate time: " << m_activateTime << endl;
	notes.clear();
	for (size_t i = 0; i < 8; i++)
	{
		Note* note = new Tapper(0);
		note->setDuration(480);
		note->setStart(m_activateTime + i * 480);
		notes.push_back(note);
		//cout << "set start: " << (m_activateTime + (i * 480)) << endl;
		//cout << notes.at(i)->getStart() << endl;
	}*/

	//these notes look correct so why not displaying correctly...
	cout << "activate time: " << m_activateTime << endl;
	cout << "end time: " << m_range + m_activateTime << endl;
	for (size_t i = 0; i < notes.size(); i++)
	{
		cout << i << " start: " << notes.at(i)->getStart() << endl;
		cout << i << " duration: " << notes.at(i)->getDuration() << endl;
	}
	cout << "end list" << endl << endl;
	

	//set up all of the rectangles in range; size, origin, position, color
	Vector2f resolution;
	resolution.x = 1920;
	resolution.y = 1080;

	float bgWidth = resolution.x * float(0.05);
	float noteWidth = resolution.x * float(0.05);
	//set horizontal position (same for all notes)
	Vector2f position;
	if (m_player == P1)
	{
		position.x = resolution.x / 2.0 - bgWidth; //slightly left of center
	}
	else
	{
		//position.x = resolution.x / 2.0 + bgWidth * float(0.5); //slightly right of center
		position.x = resolution.x / 2.0;
	}

	/*
	Color noteColor;
	if(m_color == Color::)*/
	Color noteColor;
	if (m_color == Color::Black)
	{
		noteColor = Color::White;
	}
	else
		noteColor = Color::Black;
	if (m_player == P1)
	{
		noteColor = Color(0, 100, 255, 150);
	}
	else
		noteColor = Color(255, 0, 100, 150);
	
	//loop to set up note rectangles
	for (size_t i = 0; i < notes.size(); i++)
	{
		RectangleShape* rect = new RectangleShape();
		rect->setFillColor(noteColor);
		rect->setOutlineColor(m_color);
		rect->setOutlineThickness(1.0);

		//calculate height, set size
		float noteHeightRatio = notes.at(i)->getDuration() * 1.0 / m_displayRange;
		float noteHeight = noteHeightRatio * resolution.y;
		Vector2f noteSize = { noteWidth, noteHeight };
		Vector2f tapperSize = { noteWidth, noteHeight / 4 };
		//Vector2f tapperSize = { noteWidth, noteHeight / 2};
		if (notes.at(i)->isTapper())
			rect->setSize(tapperSize);
		else
			rect->setSize(noteSize);
		//rect->setSize(noteSize);

		//set origin to center bottom
		FloatRect noteRect = rect->getGlobalBounds();
		//rect->setOrigin(noteRect.width / 2.0, noteRect.height);
		rect->setOrigin(0, noteRect.height);
		//is set scale necessary?

		//position relative to bar
		double positionRatio = (notes.at(i)->getStart() - m_activateTime) * 1.0 / m_displayRange;
		//position on screen
		Vector2f notePosition;
		notePosition.y = (1 - positionRatio) * resolution.y;
		notePosition.x = position.x;
		/*
		if (i == 0)
		{
			cout << "note start: " << notes.at(i)->getStart() << endl;
			cout << "activation time: " << m_activateTime << endl;
			cout << "difference: " << (notes.at(i)->getStart() - m_activateTime) << endl;
			cout << "display range: " << m_displayRange << endl;
			cout << "total range: " << m_range << endl;
			cout << "position ratio: " << positionRatio << endl;
			cout << "1 - ratio: " << 1 - positionRatio << endl;
			cout << "position: " << position.y << endl;
		}*/
		rect->setPosition(notePosition);

		m_rects.push_back(rect);
	}
	//tack the background rect at the end
	//or the start?
	RectangleShape* bg = new RectangleShape();

	//set bg colors
	Color bg_fill = m_color;
	Color bg_outline;
	if (m_color == Color::Black)
	{
		bg_outline = Color::White;
	}
	else
	{ //use black bg for any color that isnt black
		bg_outline = Color::Black;
	}
	/*
	//testing opposite color scheme
	bg_fill = m_color;
	if (m_color == Color::Black)
	{
		bg_outline = Color::White;
	}
	else
	{ //use black bg for any note color that isnt black
		bg_outline = Color::Black;
	}*/
	bg_fill = Color::Transparent; //only show the outline of bar
	bg->setFillColor(bg_fill);
	bg->setOutlineColor(bg_outline);
	bg->setOutlineThickness(3.0);

	//set bg size
	float bg_width = resolution.x * float(0.05);
	Vector2f bg_size = { bg_width, resolution.y };
	bg->setSize(bg_size);
	//set bg origin to center bottom
	FloatRect bg_rect = bg->getGlobalBounds();
	//bg->setOrigin(bg_rect.width / 2, bg_rect.height);
	//set origin to bottom left
	bg->setOrigin(0, bg_rect.height);

	Vector2f bg_position;
	if (m_player == P1)
	{
		bg_position.x = resolution.x / 2.0 - bg_width; //slightly left of center
	}
	else
	{
		//bg_position.x = resolution.x / 2.0 + bg_width / 2.0; //slightly right of center
		bg_position.x = resolution.x / 2.0;
	}
	bg_position.y = resolution.y;
	bg_position.x = position.x; //temp patch between the two bgwidth vars
	bg->setPosition(bg_position);


	m_rects.push_back(bg);

}

void RhythmBar::update(int midiTime)
{
	//check if active
	//update positions of rectangles (scrolling down)
	if (m_active)
	{
		if (midiTime > m_activateTime + m_range)
		{
			m_active = false;
			//deactivate, loop through and delete rectangles
			//call deactivate in Battle::updateInput()?
			//deactivate();
		}
		else
		{
			//adjust all positions except bg (last index)
			int elapsedTime = midiTime - m_lastUpdated;
			//Vector2f resolution;
			//resolution.y = 1080;
			Vector2f resolution;
			resolution.y = VideoMode::getDesktopMode().height;
			double moveRatio = (elapsedTime) * 1.0 / m_displayRange;
			cout << "Move ratio: " << moveRatio << endl;
			Vector2f offset;
			offset.x = 0.0;
			offset.y = moveRatio * resolution.y;
			//cout << "Y offset: " << offset.y << endl;
			for (size_t i = 0; i < m_rects.size() - 1; i++)
			{
				m_rects.at(i)->move(offset);
			}
			m_lastUpdated = midiTime; //WAIT HOW DOES THIS WORK?
			//m_lastUpdated += elapsedTime;
		}
	}
}

bool RhythmBar::getActive()
{
	return m_active;
}