@interface _UITapticEngine : NSObject
- (void)actuateFeedback:(NSInteger)count;
@end

@interface UIDevice (Private)
- (_UITapticEngine *)_tapticEngine;
@end

@interface UIInteractionProgress : NSObject
@end
@interface UIPreviewForceInteractionProgress : UIInteractionProgress
- (id)initWithGestureRecognizer:(id)arg1;
@end

@interface SBApplication : NSObject
@property(copy, nonatomic) NSArray *dynamicShortcutItems;
@property(copy, nonatomic) NSArray *staticShortcutItems;
- (void)loadStaticShortcutItemsFromInfoDictionary:(id)arg1 bundle:(id)arg2;
- (NSString*)bundleIdentifier;
- (NSString*)displayName;
@end;

@interface SBIcon : NSObject
- (_Bool)isFolderIcon;
- (_Bool)isNewsstandIcon;
- (void)launch; 
- (void)launchFromLocation:(NSInteger)location; 
- (void)launchFromLocation:(NSInteger)location context:(id)context; 
- (SBApplication*)application;

- (void)openApp;

@end

@interface SBIconView : UIView
@property(retain, nonatomic) SBIcon *icon;
@property(assign, getter = isHighlighted) BOOL highlighted;
@property(retain, nonatomic) UIPreviewForceInteractionProgress *shortcutMenuPresentProgress; 
@property(retain, nonatomic) UILongPressGestureRecognizer *shortcutMenuPeekGesture; 
+ (id)sharedInstance;
- (void)_handleSecondHalfLongPressTimer:(id)arg1;
- (void)cancelLongPressTimer;
//New:
- (void)sf_method:(NSInteger)method;
- (void)sf_swipe:(UISwipeGestureRecognizer *)gesture;
- (void)sf_singleTap:(UITapGestureRecognizer *)gesture;
- (void)sf_doubleTap:(UITapGestureRecognizer *)gesture;
- (void)sf_shortHold:(UILongPressGestureRecognizer *)gesture;
- (BOOL)isFolderIconView;
@end

@class SBSApplicationShortcutIcon;
@interface SBSApplicationShortcutItem : NSObject
@property (nonatomic, copy) NSString *type;
- (id)icon;
- (void)setIcon:(id)arg1;
- (void)setLocalizedSubtitle:(id)arg1;
- (void)setLocalizedTitle:(id)arg1;
- (void)setType:(NSString *)arg1;
@end

@interface SBApplicationShortcutMenuItemView : UIView
@property(readonly, nonatomic) long long menuPosition; 
@property(retain, nonatomic) SBSApplicationShortcutItem *shortcutItem; 
@property(nonatomic) _Bool highlighted; 
+ (id)_imageForShortcutItem:(id)arg1 application:(id)arg2 assetManagerProvider:(id)arg3 monogrammerProvider:(id)arg4 maxHeight:(double *)arg5;
@end
@class SBApplicationShortcutMenuContentView;
@protocol SBApplicationShortcutMenuContentViewDelegate <NSObject>
- (void)menuContentView:(SBApplicationShortcutMenuContentView *)arg1 activateShortcutItem:(SBSApplicationShortcutItem *)arg2 index:(long long)arg3;
- (_Bool)menuContentView:(SBApplicationShortcutMenuContentView *)arg1 canActivateShortcutItem:(SBSApplicationShortcutItem *)arg2;
@end
@interface SBApplicationShortcutMenuContentView : UIView <SBApplicationShortcutMenuContentViewDelegate>
@property(assign,nonatomic) id <SBApplicationShortcutMenuContentViewDelegate> delegate;
- (id)initWithInitialFrame:(struct CGRect)arg1 containerBounds:(struct CGRect)arg2 orientation:(long long)arg3 shortcutItems:(id)arg4 application:(id)arg5;
- (void)_handlePress:(id)arg1;
- (double)_rowHeight;
- (void)_populateRowsWithShortcutItems:(id)arg1 application:(id)arg2;
@end
@class SBApplicationShortcutMenu;
@protocol SBApplicationShortcutMenuDelegate <NSObject>
- (void)applicationShortcutMenu:(SBApplicationShortcutMenu *)arg1 launchApplicationWithIconView:(SBIconView *)arg2;
- (void)applicationShortcutMenu:(SBApplicationShortcutMenu *)arg1 startEditingForIconView:(SBIconView *)arg2;
- (void)applicationShortcutMenu:(SBApplicationShortcutMenu *)arg1 activateShortcutItem:(SBSApplicationShortcutItem *)arg2 index:(long long)arg3;

@optional
- (void)applicationShortcutMenuDidPresent:(SBApplicationShortcutMenu *)arg1;
- (void)applicationShortcutMenuDidDismiss:(SBApplicationShortcutMenu *)arg1;
@end
@interface SBApplicationShortcutMenu : UIView
@property(retain, nonatomic) SBApplication *application; 
@property(retain ,nonatomic) id <SBApplicationShortcutMenuDelegate> applicationShortcutMenuDelegate; 
- (id)initWithFrame:(CGRect)arg1 application:(id)arg2 iconView:(id)arg3 interactionProgress:(id)arg4 orientation:(long long)arg5;
- (void)presentAnimated:(_Bool)arg1;
- (void)menuContentView:(id)arg1 activateShortcutItem:(id)arg2 index:(long long)arg3;
- (void)updateFromPressGestureRecognizer:(id)arg1;
@end


@interface SBIconController : UIViewController <SBApplicationShortcutMenuDelegate>
@property(retain, nonatomic) SBApplicationShortcutMenu *presentedShortcutMenu;
+ (id)sharedInstance;
- (void)_revealMenuForIconView:(id)arg1 presentImmediately:(BOOL)arg2;
- (BOOL)_canRevealShortcutMenu;
- (BOOL)isEditing;
- (void)iconHandleLongPress:(id)arg1;
- (void)setIsEditing:(_Bool)arg1;
- (void)_handleShortcutMenuPeek:(UILongPressGestureRecognizer *)recognizer ;
- (void)iconTapped:(SBIconView *)iconView;
- (_Bool)hasOpenFolder;
- (void)scrollToIconListContainingIcon:(SBIcon *)icon animate:(_Bool)arg2;
-(void)openFolder:(id)folder animated:(BOOL)animated;

- (BOOL)isFolderIconView:(SBIconView *)view;
- (void)launchFirstApp:(SBIconView *)iconView;
@end


@interface SBFolder : NSObject
- (SBIcon *)iconAtIndexPath:(NSIndexPath *)indexPath;
- (void)openFirstApp;
- (void)openSecondApp; 
@end

@interface SBFolderIcon : SBIcon
- (SBFolder *)folder;
@end

@interface SBFolderIconView : SBIconView
- (SBFolderIcon*)folderIcon;
@end


@interface SBIconViewMap
+ (id)homescreenMap;
- (SBIconView *)mappedIconViewForIcon:(SBIcon *)icon;
- (SBIconView *)iconViewForIcon:(SBIcon *)icon;
- (SBIconView *)_iconViewForIcon:(SBIcon *)icon;
@end

@interface SBApplicationShortcutStoreManager : NSObject
+ (id)sharedManager;
- (void)saveSynchronously;
- (void)setShortcutItems:(id)arg1 forBundleIdentifier:(id)arg2;
- (id)shortcutItemsForBundleIdentifier:(id)arg1;
- (id)init;
@end


@interface UIApplication (Private)
-(BOOL)launchApplicationWithIdentifier:(NSString*)identifier suspended:(BOOL)suspended;
@end

@interface SBIconGridImage
+ (struct CGRect)rectAtIndex:(NSUInteger)index maxCount:(NSUInteger)count;
@end