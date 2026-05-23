/*******************************************************************************
The content of this file includes portions of the proprietary AUDIOKINETIC Wwise
Technology released in source code form as part of the game integration package.
The content of this file may not be used without valid licenses to the
AUDIOKINETIC Wwise Technology.
Note that the use of the game engine is subject to the Unreal(R) Engine End User
License Agreement at https://www.unrealengine.com/en-US/eula/unreal
 
License Usage
 
Licensees holding valid licenses to the AUDIOKINETIC Wwise Technology may use
this file in accordance with the end user license agreement provided with the
software or, alternatively, in accordance with the terms contained
in a written agreement between you and Audiokinetic Inc.
Copyright (c) 2026 Audiokinetic Inc.
*******************************************************************************/


#include "Wwise/Packaging/WwisePackagingSettingsDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailCustomization.h"
#include "Widgets/Input/SButton.h"

#include "Wwise/Packaging/WwisePackagingSettings.h"

#define LOCTEXT_NAMESPACE "WwisePackagingSettingsDetails"

EVisibility FWwisePackagingSettingsDetails::IsDisplayPreviewVisible() const
{
	return IsDisplayPreviewEnabled() ? EVisibility::Visible : EVisibility::Hidden;
}

bool FWwisePackagingSettingsDetails::IsDisplayPreviewEnabled() const
{
	if (!Settings.IsValid())
	{
		return false;
	}
	return Settings->bPackageAsBulkData;
}

TSharedRef<IDetailCustomization> FWwisePackagingSettingsDetails::MakeInstance()
{
	return MakeShareable(new FWwisePackagingSettingsDetails);
}

void FWwisePackagingSettingsDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UWwisePackagingSettings* PackagingSettings = GetMutableDefault<UWwisePackagingSettings>();
	
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	check(ObjectsBeingCustomized.Num() == 1);

	DetailBuilder.EditCategory("Cooking");
	IDetailCategoryBuilder& WwisePackagingCategory = DetailBuilder.EditCategory("DefaultGroupPreview");
	TWeakObjectPtr<UWwisePackagingSettings> CustomizedSettings = Cast<UWwisePackagingSettings>(ObjectsBeingCustomized[0].Get());
	this->Settings = CustomizedSettings;
	
	WwisePackagingCategory.AddCustomRow(LOCTEXT("WwisePackagingListRefresh", "WwisePackagingListRefresh"))
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(5)
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("ViewDefaultGroup", "View Gameplay Modules using Default Asset Library Group"))
				.ToolTipText(LOCTEXT("ViewDefaultGroup_Tooltip", "View the Gameplay Modules that will use the Default Gameplay Module"))
				.OnClicked_Lambda([this, CustomizedSettings]()
				{
					CustomizedSettings->ProcessGameplayModulesUsingDefaultGroup();
					return(FReply::Handled());
				})
				.Visibility_Raw(this, &FWwisePackagingSettingsDetails::IsDisplayPreviewVisible)
				.IsEnabled_Raw(this, &FWwisePackagingSettingsDetails::IsDisplayPreviewEnabled)
			]
		];
}

#undef LOCTEXT_NAMESPACE