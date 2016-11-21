/*
	Author: Varun Nagpal
	
	Test 1. Visitor
	-Create an Interface or Abstract base Class 'Shape'.
	-Implement three concrete Shapes: 'Circle', 'Rectangle', 'Triangle'.
	-Apply the visitor pattern to your data model.
	-Write an AreaVisitor that computes the area of the shapes.
	-Write a main that makes an arbitrary instance of a data model and apply the AreaVisitor.
*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>

//=============================== Global Constants ===========================//
const double PI = 3.141592653589793238463;
//============================================================================//


//=============================== Forward declarations =======================//
class IShapeVisitor;
//============================================================================//


//=============================== Geometry Classes ===========================//

//------------------------------ Abstract Shape class-------------------------//
class IShape
{
	protected:
		std::string _name;

	public:
		IShape( std::string name );
		std::string getName() const;
		virtual ~IShape() = 0;
		virtual void Execute( IShapeVisitor & visitor ) = 0;
};
//----------------------------------------------------------------------------//

//-----------------------------------Circle Shape ----------------------------//
class Circle : public IShape
{
	private:
		double _radius;
		
	public:
		explicit Circle( std::string name, double radius = 0.0 );
		~Circle();
		
		void setRadius( double radius );
		double getRadius() const;
		
		void Execute( IShapeVisitor & visitor ) override;
};

//----------------------------------------------------------------------------//

//--------------------------------Rectangle shape ----------------------------//
class Rectangle : public IShape
{
	private:
		double _length;
		double _breadth;
		
	public:
		explicit Rectangle( std::string name,
							double length = 0.0,
							double breadth = 0.0 );
		~Rectangle();
		
		void setLength( double length );
		void setBreadth( double breadth );
		
		double getLength() const;
		double getBreadth() const;
		
		void Execute( IShapeVisitor & visitor ) override;
};

//----------------------------------------------------------------------------//

//--------------------------------Triangle shape -----------------------------//
class Triangle : public IShape
{
	private:
		double _base;
		double _height;
		
	public:
		explicit Triangle( std::string name,
						   double base = 0.0,
						   double height = 0.0 );
		~Triangle();

		void setBase( double base );
		void setHeight( double height );
		
		double getBase() const;
		double getHeight() const;
		
		void Execute( IShapeVisitor & visitor ) override;
};
//----------------------------------------------------------------------------//

//============================================================================//


//=============================== Shape Visitor Classes ======================//

//------------------------------Abstract visitor for a Shape ------------------//
class IShapeVisitor
{
	public:
		IShapeVisitor();
		virtual ~IShapeVisitor() = 0;
		virtual void visit( Circle & c) = 0;
		virtual void visit( Rectangle & r) = 0;
		virtual void visit( Triangle & t) = 0;
};
//----------------------------------------------------------------------------//

//------------------------- Area visitor for a Shape --------------------//
class AreaVisitor : public IShapeVisitor
{
	private:
		double _area;
		void printArea( IShape const  & shape ) const;
		
	public:
		AreaVisitor();
		~AreaVisitor();
		virtual void visit( Circle & c) override;
		virtual void visit( Rectangle & r) override;
		virtual void visit( Triangle & t) override;
		
		double getArea() const;
};
//----------------------------------------------------------------------------//

//=============================== Implementation =============================//

//------------------------------- Abstract Shape Implementation---------------//
IShape::IShape( std::string name ) : _name( name )
{
	// Nothing	
}
		
IShape::~IShape()
{
	// Nothing
}

std::string IShape::getName() const
{
	return _name;
}
//----------------------------------------------------------------------------//

//--------------------------- Circle Implementation---------------------------//
Circle::Circle( std::string name, double radius) :
	IShape( name ),
	_radius( radius )
{
	// Nothing
};

Circle::~Circle()
{
	// Nothing
}

void Circle::setRadius( double radius )
{
	_radius = radius;
}

double Circle::getRadius() const
{
	return _radius;
}
		
void Circle::Execute( IShapeVisitor & visitor )
{
	visitor.visit( *this );	
}
//----------------------------------------------------------------------------//

//-------------------------- Rectangle Implementation ------------------------//
Rectangle::Rectangle( std::string name, double length, double breadth ) : 
	IShape( name ),
	_length( length ),
	_breadth( breadth )
{
	// Nothing
}

Rectangle::~Rectangle()
{
	// Nothing
}

void Rectangle::setLength( double length )
{
	_length = length;
}

void Rectangle::setBreadth( double breadth )
{
	_breadth = breadth;
}
		
double Rectangle::getLength() const
{
	return _length;
}

double Rectangle::getBreadth() const
{
	return _breadth;
}
		
void Rectangle::Execute( IShapeVisitor & visitor )
{
	visitor.visit( *this );
}
//----------------------------------------------------------------------------//

//-------------------------- Triangle Implementation -------------------------//
Triangle::Triangle( std::string name, double base, double height) :
	IShape( name ),
	_base( base ),
	_height( height )
{
	
}

Triangle::~Triangle()
{
	
}

void Triangle::setBase( double base )
{
	_base = base;
}

void Triangle::setHeight( double height )
{
	_height = height;
}

double Triangle::getBase() const
{
	return _base;	
}

double Triangle::getHeight() const
{
	return _height;
}

void Triangle::Execute( IShapeVisitor & visitor )
{
	visitor.visit( *this );
}
//----------------------------------------------------------------------------//

//-------------------------- Abstract Visitor Implementation------------------//
IShapeVisitor::IShapeVisitor()
{
	// Nothing
}

IShapeVisitor::~IShapeVisitor()
{
	// Nothing
}
//----------------------------------------------------------------------------//

//-------------------------- Area Visitor Implementation----------------------//
AreaVisitor::AreaVisitor() : _area( 0.0 )
{
	// Nothing
}

AreaVisitor::~AreaVisitor()
{
	// Nothing
}

void AreaVisitor::visit( Circle & c)
{
	double r = c.getRadius();
	_area = PI * r * r;
	printArea( c );
}

void AreaVisitor::visit( Rectangle & r)
{
	double l = r.getLength();
	double b = r.getBreadth();
	_area = l * b;
	printArea( r );
}

void AreaVisitor::visit( Triangle & t)
{
	double b = t.getBase();
	double h = t.getHeight();
	_area = 0.5 * b * h;
	printArea( t );
}

void AreaVisitor::printArea( IShape const & shape ) const
{
	std::cout << "Area of " << shape.getName() << " is " << _area << std::endl;
}

double AreaVisitor::getArea() const
{
	return _area;
}
//----------------------------------------------------------------------------//

//============================================================================//

//=================================== Main ===================================//
int main() 
{
	// List of arbitrary shapes
	std::vector<std::unique_ptr<IShape>> vecShapes;
	
	// Add instances of some arbitrary shapes to the list
	double size = 2.5;
	std::string shapeName("Circle");
	vecShapes.push_back( std::make_unique<Circle>( shapeName, size ) );
	shapeName = "Square";
	vecShapes.push_back( std::make_unique<Rectangle>( shapeName , size, size ) );
	shapeName = "Triangle";
	vecShapes.push_back( std::make_unique<Triangle>( shapeName, size, size ) );
	
	// Create an area visitor
	std::unique_ptr<IShapeVisitor> areaVisitor = std::make_unique<AreaVisitor>();
	
	// Execute the area visitor on all shapes
	for( auto const & shape: vecShapes )
		shape->Execute( *areaVisitor );
		
	return 0;
}