/*
Author: Varun Nagpal

Test 1. Multi Power Point
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class Blender
{
private:
    std::string _name;

public:
    explicit Blender( std::string name ) : _name( name ){}
    void swizzle() { std::cout << "\t" << _name << " being swizzled\n"; };
    void stop() { std::cout << "\t" << _name << " stopped\n"; };
    std::string getName() const{ return _name; }
};

class Toaster
{
private:
    std::string _name;

public:
    explicit Toaster( std::string name ) : _name( name ){}
    void startToasting(){ std::cout << "\t" << _name << " started\n"; };
    void stopToasting(){ std::cout << "\t" << _name << " stopped\n"; };
    std::string getId() const{ return _name; }
};

class Oven
{
private:
    std::string _name;

public:
    explicit Oven( std::string name ) : _name( name ) {}
    void heatUp(){ std::cout << "\t" << _name << " heating\n"; };
    void stopHeat(){ std::cout << "\t" << _name << " stopped\n"; };
    std::string getOvenName() const { return _name; }
};

class IApplianceFcd
{
protected:
    bool _isRunning;

public:
    IApplianceFcd() :_isRunning( false ){}
    virtual ~IApplianceFcd(){}
    bool isRunning() const { return _isRunning; }
    virtual std::string getName() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

class OEMBlender : public IApplianceFcd
{
private:
    Blender _blender;

public:
    explicit OEMBlender( std::string name ) : _blender( name ){}

    void start() override
    {
        _blender.swizzle();
        _isRunning = true;
    }

    void stop() override
    {
        _blender.stop();
        _isRunning = false;
    }

    std::string getName() const override{ return _blender.getName(); }
};

class OEMToaster : public IApplianceFcd
{
private:
    Toaster _toaster;

public:
    explicit OEMToaster( std::string name ) : _toaster( name ){}

    void start() override
    {
        _toaster.startToasting();
        _isRunning = true;
    }

    void stop() override
    {
        _toaster.stopToasting();
        _isRunning = false;
    }
    std::string getName() const override{ return _toaster.getId(); }
};

class OEMOven : public IApplianceFcd
{
private:
    Oven _oven;

public:
    explicit OEMOven( std::string name ) : _oven( name ){}

    void start() override
    {
        _oven.heatUp();
        _isRunning = true;
    }

    void stop() override
    {
        _oven.stopHeat();
        _isRunning = false;
    }

    std::string getName() const override{ return _oven.getOvenName(); }
};

class MultiPowerPoint
{
private:
    bool _isCurrentlyOn;
    bool _wasLastOn;
    std::vector<std::shared_ptr<IApplianceFcd>> _appliances;

public:
    MultiPowerPoint() : _isCurrentlyOn( false ), _wasLastOn( false )
    {
    }

    ~MultiPowerPoint()
    {
        off();
        _appliances.clear();
    	std::cout << std::endl << "Disconnected power supply to Multi-power point";
    }

    void AddAppliance( std::shared_ptr<IApplianceFcd> appliance )
    {
        // For safety, switch-off the power point before plugging-in new appliance
        if ( _isCurrentlyOn )
        {
            _wasLastOn = _isCurrentlyOn;
            off();
        }

        std::cout << "\t> Plugged-in " << appliance->getName() << " to Multi-powerpoint\n";
        _appliances.push_back( appliance );


        // If last time the power point was on, turn it back on 
        if ( _wasLastOn )
        {
            on();
        }
    }

    void RemoveAppliance( std::shared_ptr<IApplianceFcd> appliance )
    {
        // For safety, switch-off the power point before removing applicance
        if ( _isCurrentlyOn )
        {
            _wasLastOn = _isCurrentlyOn;
            off();
        }

        auto pos = std::find( _appliances.begin(), _appliances.end(), appliance );

        if ( pos != _appliances.end() )
        {
            std::cout << "\t> Removed " << appliance->getName() << " from Multi-powerpoint\n";
            _appliances.erase( pos );
        }

        // If last time the power point was on, turn it back on 
        if ( _wasLastOn )
        {
            on();
        }
    }

    void on()
    {
        // Switch ON only if currently switched OFF
        if ( !_isCurrentlyOn )
        {
            std::cout << std::endl << "Switching ON Multi-power point" << std::endl;
            for ( auto & appliance : _appliances )
                appliance->start();
        }
        _wasLastOn = _isCurrentlyOn;
        _isCurrentlyOn = true;
    }

    void off()
    {
        // Switch OFF only if currently switched ON
        if ( _isCurrentlyOn )
        {
            std::cout << std::endl << "Switching OFF Multi-power point" << std::endl;
            for ( auto & appliance : _appliances )
                appliance->stop();
        }

        _wasLastOn = _isCurrentlyOn;
        _isCurrentlyOn = false;
    }
};

int main()
{
    auto oven = std::make_shared<OEMOven>( "Toshiba K4 Kitchen Oven" );
    auto blender = std::make_shared<OEMBlender>( "LG OHM-207 Hand-Blender" );
    auto toaster = std::make_shared<OEMToaster>( "IFB Double toaster" );

    // Create a Multi-power point
    MultiPowerPoint mpp;

    // Connect some appliances to multi-power point
    mpp.AddAppliance( oven );
    mpp.AddAppliance( blender );
    mpp.AddAppliance( toaster );

    // Turn ON all appliances 
    mpp.on();
    mpp.on();

    // Turn off all appliances
    mpp.off();
    mpp.off();

    // Turn-on 
    mpp.on();

    // Add and remove appliances while being ON
    mpp.AddAppliance( std::make_shared<OEMToaster>( "Samsung basic toaster" ) );
    mpp.RemoveAppliance( oven );

    return 0;
}