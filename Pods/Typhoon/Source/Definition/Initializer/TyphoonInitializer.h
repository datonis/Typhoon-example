////////////////////////////////////////////////////////////////////////////////
//
//  TYPHOON FRAMEWORK
//  Copyright 2013, Jasper Blues & Contributors
//  All Rights Reserved.
//
//  NOTICE: The authors permit you to use, modify, and distribute this file
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////


#import <Foundation/Foundation.h>

@class TyphoonDefinition;
@class TyphoonParameterInjectedAsCollection;
@protocol TyphoonLogger;

typedef enum
{
    TyphoonComponentInitializerIsClassMethodGuess,
    TyphoonComponentInitializerIsClassMethodYes,
    TyphoonComponentInitializerIsClassMethodNo
} TyphoonComponentInitializerIsClassMethod;

/**
* @ingroup Definition
*
* Represents an initializer for a component.
*
* ##Initializer style injection has the following advantages:
*
* - Presents a clear contract to put the instance in the required state before use.
* - No custom lifecycle methods (before/after property injection) are required.
*
* ##Initializer injection has the following drawbacks:
*
* - Not suitable for classes with a very large number of dependencies - a very large initializer method will create poor readability.
* - Auto-injection by type is not supported.
* - No type introspection for objects injected with a text representation.
*
* Its generally recommended to use initializer-style injection, unless the above drawbacks will manifest.
*
*/
@interface TyphoonInitializer : NSObject
{
    NSMutableArray* _injectedParameters;
    NSArray* _parameterNames;
    __unsafe_unretained TyphoonDefinition* _definition;
    TyphoonComponentInitializerIsClassMethod _isClassMethodStrategy;
    SEL _selector;
}

/**
* The selector used to initialize the component.
*/
@property(nonatomic) SEL selector;

@property(nonatomic, readonly) NSArray* parameterNames;

- (id)initWithSelector:(SEL)initializer;

- (id)initWithSelector:(SEL)initializer isClassMethodStrategy:(TyphoonComponentInitializerIsClassMethod)isClassMethod;

- (TyphoonDefinition*)definition;

- (NSArray*)injectedParameters;

/* ====================================================================================================================================== */
#pragma mark - inject
/**
* Injects with the given definition.
*/
- (void)injectWithDefinition:(TyphoonDefinition*)definition;

/**
* Injects with the value represented by the given text. The text will be used to create an instance of a class matching the
* required type.
*
* @see TyphoonTypeConverterRegistry for details on declaring your own type converters.
*/
- (void)injectWithValueAsText:(NSString*)text;

/**
* Injects with the value represented by the given text. The text will be used to create an instance of the given requiredType.
*/
- (void)injectWithValueAsText:(NSString*)text requiredTypeOrNil:(id)requiredTypeOrNil;

/**
* Injects with an object instance. 
* If object is NSNumber or NSValue and argument type is scalar, pointer or NSValue-supported struct, then value will be automatically unwrapped
 * (Like KeyValueCoding does).
@code
 [initializer injectWithObjectInstance:@(YES)];
 [initializer injectWithObjectInstance:@(1.43f)];
 [initializer injectWithObjectInstance:[NSValue valueWithCGRect:defaultFrame]];
 [initializer injectWithObjectInstance:[NSValue valueWithPointer:@selector(selectorValue)]];
@endcode

To inject a class object:

@code
[initializer injectWithObjectInstance:[SomeObject class]];
@endcode

*/
- (void)injectWithObjectInstance:(id)value;

/**
* Injects with a collection of the given type.
*/
- (void)injectWithCollection:(void (^)(TyphoonParameterInjectedAsCollection*))collectionValues requiredType:(id)requiredType;


#pragma mark - injectParameterNamed:
- (void)injectParameterNamed:(NSString*)name withReference:(NSString*)reference;

- (void)injectParameterNamed:(NSString*)name withValueAsText:(NSString*)text requiredTypeOrNil:(id)classOrProtocol;

- (void)injectParameterNamed:(NSString*)name withObject:(id)value;

/**
* Injects the parameter matched by the given name with the given definition.
*/
- (void)injectParameterNamed:(NSString*)name withDefinition:(TyphoonDefinition*)definition;

/**
* Injects the parameter matched by the given name as a collection of the given requiredType.
*/
- (void)injectParameterNamed:(NSString*)name
        asCollection:(void (^)(TyphoonParameterInjectedAsCollection*))collectionValues
        requiredType:(id)requiredType;


#pragma mark - injectParameterAtIndex
/**
* Injects the parameter at the given index with the given definition.
*/
- (void)injectParameterAtIndex:(NSUInteger)index withDefinition:(TyphoonDefinition*)definition;

/**
* Injects the parameter at the given index as a collection of the given requiredType.
*/
- (void)injectParameterAtIndex:(NSUInteger)index
        asCollection:(void (^)(TyphoonParameterInjectedAsCollection*))collectionValues
        requiredType:(id)requiredType;

- (void)injectParameterAtIndex:(NSUInteger)index withReference:(NSString *)reference;

- (void)injectParameterAtIndex:(NSUInteger)index withValueAsText:(NSString*)text requiredTypeOrNil:(id)requiredClass;

- (void)injectParameterAtIndex:(NSUInteger)index withObject:(id)value;

@end
