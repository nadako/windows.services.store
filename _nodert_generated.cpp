// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Services { namespace Store { 
  v8::Local<v8::Value> WrapStoreProduct(::Windows::Services::Store::StoreProduct^ wintRtInstance);
  ::Windows::Services::Store::StoreProduct^ UnwrapStoreProduct(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreProductPagedQueryResult(::Windows::Services::Store::StoreProductPagedQueryResult^ wintRtInstance);
  ::Windows::Services::Store::StoreProductPagedQueryResult^ UnwrapStoreProductPagedQueryResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePurchaseProperties(::Windows::Services::Store::StorePurchaseProperties^ wintRtInstance);
  ::Windows::Services::Store::StorePurchaseProperties^ UnwrapStorePurchaseProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreLicense(::Windows::Services::Store::StoreLicense^ wintRtInstance);
  ::Windows::Services::Store::StoreLicense^ UnwrapStoreLicense(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreImage(::Windows::Services::Store::StoreImage^ wintRtInstance);
  ::Windows::Services::Store::StoreImage^ UnwrapStoreImage(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreVideo(::Windows::Services::Store::StoreVideo^ wintRtInstance);
  ::Windows::Services::Store::StoreVideo^ UnwrapStoreVideo(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreSku(::Windows::Services::Store::StoreSku^ wintRtInstance);
  ::Windows::Services::Store::StoreSku^ UnwrapStoreSku(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePrice(::Windows::Services::Store::StorePrice^ wintRtInstance);
  ::Windows::Services::Store::StorePrice^ UnwrapStorePrice(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePurchaseResult(::Windows::Services::Store::StorePurchaseResult^ wintRtInstance);
  ::Windows::Services::Store::StorePurchaseResult^ UnwrapStorePurchaseResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreAvailability(::Windows::Services::Store::StoreAvailability^ wintRtInstance);
  ::Windows::Services::Store::StoreAvailability^ UnwrapStoreAvailability(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreCollectionData(::Windows::Services::Store::StoreCollectionData^ wintRtInstance);
  ::Windows::Services::Store::StoreCollectionData^ UnwrapStoreCollectionData(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreSubscriptionInfo(::Windows::Services::Store::StoreSubscriptionInfo^ wintRtInstance);
  ::Windows::Services::Store::StoreSubscriptionInfo^ UnwrapStoreSubscriptionInfo(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreContext(::Windows::Services::Store::StoreContext^ wintRtInstance);
  ::Windows::Services::Store::StoreContext^ UnwrapStoreContext(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreSendRequestResult(::Windows::Services::Store::StoreSendRequestResult^ wintRtInstance);
  ::Windows::Services::Store::StoreSendRequestResult^ UnwrapStoreSendRequestResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreAppLicense(::Windows::Services::Store::StoreAppLicense^ wintRtInstance);
  ::Windows::Services::Store::StoreAppLicense^ UnwrapStoreAppLicense(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreProductResult(::Windows::Services::Store::StoreProductResult^ wintRtInstance);
  ::Windows::Services::Store::StoreProductResult^ UnwrapStoreProductResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreProductQueryResult(::Windows::Services::Store::StoreProductQueryResult^ wintRtInstance);
  ::Windows::Services::Store::StoreProductQueryResult^ UnwrapStoreProductQueryResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreConsumableResult(::Windows::Services::Store::StoreConsumableResult^ wintRtInstance);
  ::Windows::Services::Store::StoreConsumableResult^ UnwrapStoreConsumableResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreAcquireLicenseResult(::Windows::Services::Store::StoreAcquireLicenseResult^ wintRtInstance);
  ::Windows::Services::Store::StoreAcquireLicenseResult^ UnwrapStoreAcquireLicenseResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePackageUpdate(::Windows::Services::Store::StorePackageUpdate^ wintRtInstance);
  ::Windows::Services::Store::StorePackageUpdate^ UnwrapStorePackageUpdate(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePackageUpdateResult(::Windows::Services::Store::StorePackageUpdateResult^ wintRtInstance);
  ::Windows::Services::Store::StorePackageUpdateResult^ UnwrapStorePackageUpdateResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreCanAcquireLicenseResult(::Windows::Services::Store::StoreCanAcquireLicenseResult^ wintRtInstance);
  ::Windows::Services::Store::StoreCanAcquireLicenseResult^ UnwrapStoreCanAcquireLicenseResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreProductOptions(::Windows::Services::Store::StoreProductOptions^ wintRtInstance);
  ::Windows::Services::Store::StoreProductOptions^ UnwrapStoreProductOptions(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreQueueItem(::Windows::Services::Store::StoreQueueItem^ wintRtInstance);
  ::Windows::Services::Store::StoreQueueItem^ UnwrapStoreQueueItem(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePackageInstallOptions(::Windows::Services::Store::StorePackageInstallOptions^ wintRtInstance);
  ::Windows::Services::Store::StorePackageInstallOptions^ UnwrapStorePackageInstallOptions(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreUninstallStorePackageResult(::Windows::Services::Store::StoreUninstallStorePackageResult^ wintRtInstance);
  ::Windows::Services::Store::StoreUninstallStorePackageResult^ UnwrapStoreUninstallStorePackageResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreQueueItemStatus(::Windows::Services::Store::StoreQueueItemStatus^ wintRtInstance);
  ::Windows::Services::Store::StoreQueueItemStatus^ UnwrapStoreQueueItemStatus(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreQueueItemCompletedEventArgs(::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ wintRtInstance);
  ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ UnwrapStoreQueueItemCompletedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorePackageLicense(::Windows::Services::Store::StorePackageLicense^ wintRtInstance);
  ::Windows::Services::Store::StorePackageLicense^ UnwrapStorePackageLicense(Local<Value> value);
  
  v8::Local<v8::Value> WrapStoreRequestHelper(::Windows::Services::Store::StoreRequestHelper^ wintRtInstance);
  ::Windows::Services::Store::StoreRequestHelper^ UnwrapStoreRequestHelper(Local<Value> value);
  



  static void InitStorePurchaseStatusEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorePurchaseStatus").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("succeeded").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePurchaseStatus::Succeeded)));
    Nan::Set(enumObject, Nan::New<String>("alreadyPurchased").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePurchaseStatus::AlreadyPurchased)));
    Nan::Set(enumObject, Nan::New<String>("notPurchased").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePurchaseStatus::NotPurchased)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePurchaseStatus::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("serverError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePurchaseStatus::ServerError)));
  }

  static void InitStoreConsumableStatusEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreConsumableStatus").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("succeeded").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreConsumableStatus::Succeeded)));
    Nan::Set(enumObject, Nan::New<String>("insufficentQuantity").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreConsumableStatus::InsufficentQuantity)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreConsumableStatus::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("serverError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreConsumableStatus::ServerError)));
  }

  static void InitStoreDurationUnitEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreDurationUnit").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("minute").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Minute)));
    Nan::Set(enumObject, Nan::New<String>("hour").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Hour)));
    Nan::Set(enumObject, Nan::New<String>("day").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Day)));
    Nan::Set(enumObject, Nan::New<String>("week").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Week)));
    Nan::Set(enumObject, Nan::New<String>("month").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Month)));
    Nan::Set(enumObject, Nan::New<String>("year").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreDurationUnit::Year)));
  }

  static void InitStorePackageUpdateStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorePackageUpdateState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("pending").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::Pending)));
    Nan::Set(enumObject, Nan::New<String>("downloading").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::Downloading)));
    Nan::Set(enumObject, Nan::New<String>("deploying").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::Deploying)));
    Nan::Set(enumObject, Nan::New<String>("completed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::Completed)));
    Nan::Set(enumObject, Nan::New<String>("canceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::Canceled)));
    Nan::Set(enumObject, Nan::New<String>("otherError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::OtherError)));
    Nan::Set(enumObject, Nan::New<String>("errorLowBattery").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::ErrorLowBattery)));
    Nan::Set(enumObject, Nan::New<String>("errorWiFiRecommended").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::ErrorWiFiRecommended)));
    Nan::Set(enumObject, Nan::New<String>("errorWiFiRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StorePackageUpdateState::ErrorWiFiRequired)));
  }

  static void InitStoreCanLicenseStatusEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreCanLicenseStatus").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("notLicensableToUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreCanLicenseStatus::NotLicensableToUser)));
    Nan::Set(enumObject, Nan::New<String>("licensable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreCanLicenseStatus::Licensable)));
    Nan::Set(enumObject, Nan::New<String>("licenseActionNotApplicableToProduct").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreCanLicenseStatus::LicenseActionNotApplicableToProduct)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreCanLicenseStatus::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("serverError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreCanLicenseStatus::ServerError)));
  }

  static void InitStoreQueueItemStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreQueueItemState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("active").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemState::Active)));
    Nan::Set(enumObject, Nan::New<String>("completed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemState::Completed)));
    Nan::Set(enumObject, Nan::New<String>("canceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemState::Canceled)));
    Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemState::Error)));
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemState::Paused)));
  }

  static void InitStoreQueueItemExtendedStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreQueueItemExtendedState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("activePending").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActivePending)));
    Nan::Set(enumObject, Nan::New<String>("activeStarting").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActiveStarting)));
    Nan::Set(enumObject, Nan::New<String>("activeAcquiringLicense").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActiveAcquiringLicense)));
    Nan::Set(enumObject, Nan::New<String>("activeDownloading").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActiveDownloading)));
    Nan::Set(enumObject, Nan::New<String>("activeRestoringData").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActiveRestoringData)));
    Nan::Set(enumObject, Nan::New<String>("activeInstalling").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::ActiveInstalling)));
    Nan::Set(enumObject, Nan::New<String>("completed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::Completed)));
    Nan::Set(enumObject, Nan::New<String>("canceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::Canceled)));
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::Paused)));
    Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::Error)));
    Nan::Set(enumObject, Nan::New<String>("pausedPackagesInUse").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::PausedPackagesInUse)));
    Nan::Set(enumObject, Nan::New<String>("pausedLowBattery").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::PausedLowBattery)));
    Nan::Set(enumObject, Nan::New<String>("pausedWiFiRecommended").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::PausedWiFiRecommended)));
    Nan::Set(enumObject, Nan::New<String>("pausedWiFiRequired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::PausedWiFiRequired)));
    Nan::Set(enumObject, Nan::New<String>("pausedReadyToInstall").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemExtendedState::PausedReadyToInstall)));
  }

  static void InitStoreQueueItemKindEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreQueueItemKind").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("install").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemKind::Install)));
    Nan::Set(enumObject, Nan::New<String>("update").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemKind::Update)));
    Nan::Set(enumObject, Nan::New<String>("repair").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreQueueItemKind::Repair)));
  }

  static void InitStoreUninstallStorePackageStatusEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StoreUninstallStorePackageStatus").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("succeeded").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreUninstallStorePackageStatus::Succeeded)));
    Nan::Set(enumObject, Nan::New<String>("canceledByUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreUninstallStorePackageStatus::CanceledByUser)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreUninstallStorePackageStatus::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("uninstallNotApplicable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreUninstallStorePackageStatus::UninstallNotApplicable)));
    Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Services::Store::StoreUninstallStorePackageStatus::Error)));
  }

  static bool IsStoreContractJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Services::Store::StoreContract StoreContractFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Services::Store::StoreContract returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> StoreContractToJsObject(::Windows::Services::Store::StoreContract value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }
  static bool IsStorePackageUpdateStatusJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("packageFamilyName").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsString()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("packageDownloadSizeInBytes").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("packageBytesDownloaded").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("packageDownloadProgress").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("totalDownloadProgress").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("packageUpdateState").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Services::Store::StorePackageUpdateStatus StorePackageUpdateStatusFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Services::Store::StorePackageUpdateStatus returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("packageFamilyName").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.PackageFamilyName = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), Nan::Get(obj,symbol).ToLocalChecked())));
    }
    
    symbol = Nan::New<String>("packageDownloadSizeInBytes").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.PackageDownloadSizeInBytes = static_cast<unsigned __int64>(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("packageBytesDownloaded").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.PackageBytesDownloaded = static_cast<unsigned __int64>(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("packageDownloadProgress").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.PackageDownloadProgress = Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0);
    }
    
    symbol = Nan::New<String>("totalDownloadProgress").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.TotalDownloadProgress = Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0);
    }
    
    symbol = Nan::New<String>("packageUpdateState").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.PackageUpdateState = static_cast<::Windows::Services::Store::StorePackageUpdateState>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> StorePackageUpdateStatusToJsObject(::Windows::Services::Store::StorePackageUpdateStatus value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("packageFamilyName").ToLocalChecked(), NodeRT::Utils::NewString(value.PackageFamilyName->Data()));
    Nan::Set(obj, Nan::New<String>("packageDownloadSizeInBytes").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.PackageDownloadSizeInBytes)));
    Nan::Set(obj, Nan::New<String>("packageBytesDownloaded").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.PackageBytesDownloaded)));
    Nan::Set(obj, Nan::New<String>("packageDownloadProgress").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.PackageDownloadProgress)));
    Nan::Set(obj, Nan::New<String>("totalDownloadProgress").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.TotalDownloadProgress)));
    Nan::Set(obj, Nan::New<String>("packageUpdateState").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(value.PackageUpdateState)));

    return scope.Escape(obj);
  }


  class StoreProduct : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreProduct").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getIsAnySkuInstalledAsync", GetIsAnySkuInstalledAsync);
            Nan::SetPrototypeMethod(localRef, "requestPurchaseAsync", RequestPurchaseAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasDigitalDownload").ToLocalChecked(), HasDigitalDownloadGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("images").ToLocalChecked(), ImagesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inAppOfferToken").ToLocalChecked(), InAppOfferTokenGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isInUserCollection").ToLocalChecked(), IsInUserCollectionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("keywords").ToLocalChecked(), KeywordsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("language").ToLocalChecked(), LanguageGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("linkUri").ToLocalChecked(), LinkUriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("price").ToLocalChecked(), PriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("productKind").ToLocalChecked(), ProductKindGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("skus").ToLocalChecked(), SkusGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storeId").ToLocalChecked(), StoreIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videos").ToLocalChecked(), VideosGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreProduct").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreProduct(::Windows::Services::Store::StoreProduct^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreProduct^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreProduct^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreProduct *wrapperInstance = new StoreProduct(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreProduct^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreProduct^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreProduct(winRtInstance));
    }

    static void GetIsAnySkuInstalledAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetIsAnySkuInstalledAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestPurchaseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StorePurchaseResult^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestPurchaseAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[0]))
      {
        try
        {
          ::Windows::Services::Store::StorePurchaseProperties^ arg0 = UnwrapStorePurchaseProperties(info[0]);
          
          op = wrapper->_instance->RequestPurchaseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePurchaseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePurchaseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Description;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HasDigitalDownloadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        bool result = wrapper->_instance->HasDigitalDownload;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ImagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreImage^>^ result = wrapper->_instance->Images;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreImage^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreImage^ val) -> Local<Value> {
              return WrapStoreImage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreImage^ {
              return UnwrapStoreImage(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InAppOfferTokenGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InAppOfferToken;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsInUserCollectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        bool result = wrapper->_instance->IsInUserCollection;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void KeywordsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->Keywords;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Language;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LinkUriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->LinkUri;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Services::Store::StorePrice^ result = wrapper->_instance->Price;
        info.GetReturnValue().Set(WrapStorePrice(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProductKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ProductKind;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SkusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreSku^>^ result = wrapper->_instance->Skus;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreSku^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreSku^ val) -> Local<Value> {
              return WrapStoreSku(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreSku^ {
              return UnwrapStoreSku(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StoreIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->StoreId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideosGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProduct^>(info.This())) {
        return;
      }

      StoreProduct *wrapper = StoreProduct::Unwrap<StoreProduct>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreVideo^>^ result = wrapper->_instance->Videos;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreVideo^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreVideo^ val) -> Local<Value> {
              return WrapStoreVideo(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreVideo^ {
              return UnwrapStoreVideo(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreProduct^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreProduct(::Windows::Services::Store::StoreProduct^ wintRtInstance);
      friend ::Windows::Services::Store::StoreProduct^ UnwrapStoreProduct(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreProduct::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreProduct(::Windows::Services::Store::StoreProduct^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreProduct::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreProduct^ UnwrapStoreProduct(Local<Value> value) {
     return StoreProduct::Unwrap<StoreProduct>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreProduct(Local<Object> exports) {
    StoreProduct::Init(exports);
  }

  class StoreProductPagedQueryResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreProductPagedQueryResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getNextAsync", GetNextAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasMoreResults").ToLocalChecked(), HasMoreResultsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("products").ToLocalChecked(), ProductsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreProductPagedQueryResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreProductPagedQueryResult(::Windows::Services::Store::StoreProductPagedQueryResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreProductPagedQueryResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreProductPagedQueryResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreProductPagedQueryResult *wrapperInstance = new StoreProductPagedQueryResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreProductPagedQueryResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreProductPagedQueryResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreProductPagedQueryResult(winRtInstance));
    }

    static void GetNextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreProductPagedQueryResult *wrapper = StoreProductPagedQueryResult::Unwrap<StoreProductPagedQueryResult>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductPagedQueryResult^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetNextAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductPagedQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductPagedQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info.This())) {
        return;
      }

      StoreProductPagedQueryResult *wrapper = StoreProductPagedQueryResult::Unwrap<StoreProductPagedQueryResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HasMoreResultsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info.This())) {
        return;
      }

      StoreProductPagedQueryResult *wrapper = StoreProductPagedQueryResult::Unwrap<StoreProductPagedQueryResult>(info.This());

      try  {
        bool result = wrapper->_instance->HasMoreResults;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProductsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductPagedQueryResult^>(info.This())) {
        return;
      }

      StoreProductPagedQueryResult *wrapper = StoreProductPagedQueryResult::Unwrap<StoreProductPagedQueryResult>(info.This());

      try  {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Windows::Services::Store::StoreProduct^>^ result = wrapper->_instance->Products;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Windows::Services::Store::StoreProduct^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Windows::Services::Store::StoreProduct^ val) -> Local<Value> {
              return WrapStoreProduct(val);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreProductPagedQueryResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreProductPagedQueryResult(::Windows::Services::Store::StoreProductPagedQueryResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreProductPagedQueryResult^ UnwrapStoreProductPagedQueryResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreProductPagedQueryResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreProductPagedQueryResult(::Windows::Services::Store::StoreProductPagedQueryResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreProductPagedQueryResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreProductPagedQueryResult^ UnwrapStoreProductPagedQueryResult(Local<Value> value) {
     return StoreProductPagedQueryResult::Unwrap<StoreProductPagedQueryResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreProductPagedQueryResult(Local<Object> exports) {
    StoreProductPagedQueryResult::Init(exports);
  }

  class StorePurchaseProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePurchaseProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter, NameSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter, ExtendedJsonDataSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePurchaseProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePurchaseProperties(::Windows::Services::Store::StorePurchaseProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePurchaseProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePurchaseProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          winRtInstance = ref new ::Windows::Services::Store::StorePurchaseProperties(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Services::Store::StorePurchaseProperties();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePurchaseProperties *wrapperInstance = new StorePurchaseProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePurchaseProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePurchaseProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePurchaseProperties(winRtInstance));
    }





    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info.This())) {
        return;
      }

      StorePurchaseProperties *wrapper = StorePurchaseProperties::Unwrap<StorePurchaseProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info.This())) {
        return;
      }

      StorePurchaseProperties *wrapper = StorePurchaseProperties::Unwrap<StorePurchaseProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Name = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info.This())) {
        return;
      }

      StorePurchaseProperties *wrapper = StorePurchaseProperties::Unwrap<StorePurchaseProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info.This())) {
        return;
      }

      StorePurchaseProperties *wrapper = StorePurchaseProperties::Unwrap<StorePurchaseProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->ExtendedJsonData = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Services::Store::StorePurchaseProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePurchaseProperties(::Windows::Services::Store::StorePurchaseProperties^ wintRtInstance);
      friend ::Windows::Services::Store::StorePurchaseProperties^ UnwrapStorePurchaseProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePurchaseProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePurchaseProperties(::Windows::Services::Store::StorePurchaseProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePurchaseProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePurchaseProperties^ UnwrapStorePurchaseProperties(Local<Value> value) {
     return StorePurchaseProperties::Unwrap<StorePurchaseProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePurchaseProperties(Local<Object> exports) {
    StorePurchaseProperties::Init(exports);
  }

  class StoreLicense : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreLicense").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationDate").ToLocalChecked(), ExpirationDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("inAppOfferToken").ToLocalChecked(), InAppOfferTokenGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isActive").ToLocalChecked(), IsActiveGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("skuStoreId").ToLocalChecked(), SkuStoreIdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreLicense").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreLicense(::Windows::Services::Store::StoreLicense^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreLicense^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreLicense *wrapperInstance = new StoreLicense(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreLicense^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreLicense(winRtInstance));
    }





    static void ExpirationDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info.This())) {
        return;
      }

      StoreLicense *wrapper = StoreLicense::Unwrap<StoreLicense>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->ExpirationDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info.This())) {
        return;
      }

      StoreLicense *wrapper = StoreLicense::Unwrap<StoreLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InAppOfferTokenGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info.This())) {
        return;
      }

      StoreLicense *wrapper = StoreLicense::Unwrap<StoreLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InAppOfferToken;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsActiveGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info.This())) {
        return;
      }

      StoreLicense *wrapper = StoreLicense::Unwrap<StoreLicense>(info.This());

      try  {
        bool result = wrapper->_instance->IsActive;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SkuStoreIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreLicense^>(info.This())) {
        return;
      }

      StoreLicense *wrapper = StoreLicense::Unwrap<StoreLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SkuStoreId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreLicense^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreLicense(::Windows::Services::Store::StoreLicense^ wintRtInstance);
      friend ::Windows::Services::Store::StoreLicense^ UnwrapStoreLicense(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreLicense::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreLicense(::Windows::Services::Store::StoreLicense^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreLicense::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreLicense^ UnwrapStoreLicense(Local<Value> value) {
     return StoreLicense::Unwrap<StoreLicense>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreLicense(Local<Object> exports) {
    StoreLicense::Init(exports);
  }

  class StoreImage : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreImage").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("caption").ToLocalChecked(), CaptionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("height").ToLocalChecked(), HeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("imagePurposeTag").ToLocalChecked(), ImagePurposeTagGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uri").ToLocalChecked(), UriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("width").ToLocalChecked(), WidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreImage").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreImage(::Windows::Services::Store::StoreImage^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreImage^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreImage^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreImage *wrapperInstance = new StoreImage(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreImage^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreImage^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreImage(winRtInstance));
    }





    static void CaptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info.This())) {
        return;
      }

      StoreImage *wrapper = StoreImage::Unwrap<StoreImage>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Caption;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info.This())) {
        return;
      }

      StoreImage *wrapper = StoreImage::Unwrap<StoreImage>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Height;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ImagePurposeTagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info.This())) {
        return;
      }

      StoreImage *wrapper = StoreImage::Unwrap<StoreImage>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ImagePurposeTag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void UriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info.This())) {
        return;
      }

      StoreImage *wrapper = StoreImage::Unwrap<StoreImage>(info.This());

      try  {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Uri;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void WidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(info.This())) {
        return;
      }

      StoreImage *wrapper = StoreImage::Unwrap<StoreImage>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Width;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreImage^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreImage(::Windows::Services::Store::StoreImage^ wintRtInstance);
      friend ::Windows::Services::Store::StoreImage^ UnwrapStoreImage(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreImage::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreImage(::Windows::Services::Store::StoreImage^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreImage::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreImage^ UnwrapStoreImage(Local<Value> value) {
     return StoreImage::Unwrap<StoreImage>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreImage(Local<Object> exports) {
    StoreImage::Init(exports);
  }

  class StoreVideo : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreVideo").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("caption").ToLocalChecked(), CaptionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("height").ToLocalChecked(), HeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previewImage").ToLocalChecked(), PreviewImageGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("uri").ToLocalChecked(), UriGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videoPurposeTag").ToLocalChecked(), VideoPurposeTagGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("width").ToLocalChecked(), WidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreVideo").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreVideo(::Windows::Services::Store::StoreVideo^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreVideo^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreVideo^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreVideo *wrapperInstance = new StoreVideo(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreVideo^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreVideo^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreVideo(winRtInstance));
    }





    static void CaptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Caption;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Height;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviewImageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        ::Windows::Services::Store::StoreImage^ result = wrapper->_instance->PreviewImage;
        info.GetReturnValue().Set(WrapStoreImage(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void UriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Uri;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideoPurposeTagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->VideoPurposeTag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void WidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(info.This())) {
        return;
      }

      StoreVideo *wrapper = StoreVideo::Unwrap<StoreVideo>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Width;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreVideo^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreVideo(::Windows::Services::Store::StoreVideo^ wintRtInstance);
      friend ::Windows::Services::Store::StoreVideo^ UnwrapStoreVideo(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreVideo::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreVideo(::Windows::Services::Store::StoreVideo^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreVideo::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreVideo^ UnwrapStoreVideo(Local<Value> value) {
     return StoreVideo::Unwrap<StoreVideo>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreVideo(Local<Object> exports) {
    StoreVideo::Init(exports);
  }

  class StoreSku : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreSku").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getIsInstalledAsync", GetIsInstalledAsync);
            Nan::SetPrototypeMethod(localRef, "requestPurchaseAsync", RequestPurchaseAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("availabilities").ToLocalChecked(), AvailabilitiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bundledSkus").ToLocalChecked(), BundledSkusGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("collectionData").ToLocalChecked(), CollectionDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("customDeveloperData").ToLocalChecked(), CustomDeveloperDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("images").ToLocalChecked(), ImagesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isInUserCollection").ToLocalChecked(), IsInUserCollectionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isSubscription").ToLocalChecked(), IsSubscriptionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isTrial").ToLocalChecked(), IsTrialGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("language").ToLocalChecked(), LanguageGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("price").ToLocalChecked(), PriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storeId").ToLocalChecked(), StoreIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subscriptionInfo").ToLocalChecked(), SubscriptionInfoGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videos").ToLocalChecked(), VideosGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreSku").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreSku(::Windows::Services::Store::StoreSku^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreSku^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreSku^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreSku *wrapperInstance = new StoreSku(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreSku^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreSku^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreSku(winRtInstance));
    }

    static void GetIsInstalledAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetIsInstalledAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestPurchaseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StorePurchaseResult^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestPurchaseAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[0]))
      {
        try
        {
          ::Windows::Services::Store::StorePurchaseProperties^ arg0 = UnwrapStorePurchaseProperties(info[0]);
          
          op = wrapper->_instance->RequestPurchaseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePurchaseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePurchaseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void AvailabilitiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreAvailability^>^ result = wrapper->_instance->Availabilities;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreAvailability^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreAvailability^ val) -> Local<Value> {
              return WrapStoreAvailability(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreAvailability^ {
              return UnwrapStoreAvailability(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BundledSkusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->BundledSkus;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CollectionDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Services::Store::StoreCollectionData^ result = wrapper->_instance->CollectionData;
        info.GetReturnValue().Set(WrapStoreCollectionData(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CustomDeveloperDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CustomDeveloperData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Description;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ImagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreImage^>^ result = wrapper->_instance->Images;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreImage^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreImage^ val) -> Local<Value> {
              return WrapStoreImage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreImage^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreImage^ {
              return UnwrapStoreImage(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsInUserCollectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        bool result = wrapper->_instance->IsInUserCollection;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsSubscriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        bool result = wrapper->_instance->IsSubscription;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsTrialGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        bool result = wrapper->_instance->IsTrial;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Language;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Services::Store::StorePrice^ result = wrapper->_instance->Price;
        info.GetReturnValue().Set(WrapStorePrice(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StoreIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->StoreId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SubscriptionInfoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Services::Store::StoreSubscriptionInfo^ result = wrapper->_instance->SubscriptionInfo;
        info.GetReturnValue().Set(WrapStoreSubscriptionInfo(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideosGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSku^>(info.This())) {
        return;
      }

      StoreSku *wrapper = StoreSku::Unwrap<StoreSku>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreVideo^>^ result = wrapper->_instance->Videos;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreVideo^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreVideo^ val) -> Local<Value> {
              return WrapStoreVideo(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreVideo^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreVideo^ {
              return UnwrapStoreVideo(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreSku^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreSku(::Windows::Services::Store::StoreSku^ wintRtInstance);
      friend ::Windows::Services::Store::StoreSku^ UnwrapStoreSku(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreSku::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreSku(::Windows::Services::Store::StoreSku^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreSku::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreSku^ UnwrapStoreSku(Local<Value> value) {
     return StoreSku::Unwrap<StoreSku>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreSku(Local<Object> exports) {
    StoreSku::Init(exports);
  }

  class StorePrice : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePrice").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currencyCode").ToLocalChecked(), CurrencyCodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("formattedBasePrice").ToLocalChecked(), FormattedBasePriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("formattedPrice").ToLocalChecked(), FormattedPriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("formattedRecurrencePrice").ToLocalChecked(), FormattedRecurrencePriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isOnSale").ToLocalChecked(), IsOnSaleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("saleEndDate").ToLocalChecked(), SaleEndDateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePrice").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePrice(::Windows::Services::Store::StorePrice^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePrice^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePrice^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePrice *wrapperInstance = new StorePrice(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePrice^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePrice^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePrice(winRtInstance));
    }





    static void CurrencyCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CurrencyCode;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FormattedBasePriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FormattedBasePrice;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FormattedPriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FormattedPrice;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FormattedRecurrencePriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FormattedRecurrencePrice;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsOnSaleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        bool result = wrapper->_instance->IsOnSale;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SaleEndDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePrice^>(info.This())) {
        return;
      }

      StorePrice *wrapper = StorePrice::Unwrap<StorePrice>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->SaleEndDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StorePrice^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePrice(::Windows::Services::Store::StorePrice^ wintRtInstance);
      friend ::Windows::Services::Store::StorePrice^ UnwrapStorePrice(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePrice::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePrice(::Windows::Services::Store::StorePrice^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePrice::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePrice^ UnwrapStorePrice(Local<Value> value) {
     return StorePrice::Unwrap<StorePrice>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePrice(Local<Object> exports) {
    StorePrice::Init(exports);
  }

  class StorePurchaseResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePurchaseResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePurchaseResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePurchaseResult(::Windows::Services::Store::StorePurchaseResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePurchaseResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePurchaseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePurchaseResult *wrapperInstance = new StorePurchaseResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePurchaseResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePurchaseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePurchaseResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseResult^>(info.This())) {
        return;
      }

      StorePurchaseResult *wrapper = StorePurchaseResult::Unwrap<StorePurchaseResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseResult^>(info.This())) {
        return;
      }

      StorePurchaseResult *wrapper = StorePurchaseResult::Unwrap<StorePurchaseResult>(info.This());

      try  {
        ::Windows::Services::Store::StorePurchaseStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StorePurchaseResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePurchaseResult(::Windows::Services::Store::StorePurchaseResult^ wintRtInstance);
      friend ::Windows::Services::Store::StorePurchaseResult^ UnwrapStorePurchaseResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePurchaseResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePurchaseResult(::Windows::Services::Store::StorePurchaseResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePurchaseResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePurchaseResult^ UnwrapStorePurchaseResult(Local<Value> value) {
     return StorePurchaseResult::Unwrap<StorePurchaseResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePurchaseResult(Local<Object> exports) {
    StorePurchaseResult::Init(exports);
  }

  class StoreAvailability : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreAvailability").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "requestPurchaseAsync", RequestPurchaseAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("endDate").ToLocalChecked(), EndDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("price").ToLocalChecked(), PriceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storeId").ToLocalChecked(), StoreIdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreAvailability").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreAvailability(::Windows::Services::Store::StoreAvailability^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreAvailability^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreAvailability^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreAvailability *wrapperInstance = new StoreAvailability(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreAvailability^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreAvailability^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreAvailability(winRtInstance));
    }

    static void RequestPurchaseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreAvailability *wrapper = StoreAvailability::Unwrap<StoreAvailability>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StorePurchaseResult^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestPurchaseAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[0]))
      {
        try
        {
          ::Windows::Services::Store::StorePurchaseProperties^ arg0 = UnwrapStorePurchaseProperties(info[0]);
          
          op = wrapper->_instance->RequestPurchaseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePurchaseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePurchaseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void EndDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info.This())) {
        return;
      }

      StoreAvailability *wrapper = StoreAvailability::Unwrap<StoreAvailability>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->EndDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info.This())) {
        return;
      }

      StoreAvailability *wrapper = StoreAvailability::Unwrap<StoreAvailability>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PriceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info.This())) {
        return;
      }

      StoreAvailability *wrapper = StoreAvailability::Unwrap<StoreAvailability>(info.This());

      try  {
        ::Windows::Services::Store::StorePrice^ result = wrapper->_instance->Price;
        info.GetReturnValue().Set(WrapStorePrice(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StoreIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAvailability^>(info.This())) {
        return;
      }

      StoreAvailability *wrapper = StoreAvailability::Unwrap<StoreAvailability>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->StoreId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreAvailability^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreAvailability(::Windows::Services::Store::StoreAvailability^ wintRtInstance);
      friend ::Windows::Services::Store::StoreAvailability^ UnwrapStoreAvailability(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreAvailability::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreAvailability(::Windows::Services::Store::StoreAvailability^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreAvailability::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreAvailability^ UnwrapStoreAvailability(Local<Value> value) {
     return StoreAvailability::Unwrap<StoreAvailability>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreAvailability(Local<Object> exports) {
    StoreAvailability::Init(exports);
  }

  class StoreCollectionData : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreCollectionData").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("acquiredDate").ToLocalChecked(), AcquiredDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("campaignId").ToLocalChecked(), CampaignIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("developerOfferId").ToLocalChecked(), DeveloperOfferIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("endDate").ToLocalChecked(), EndDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isTrial").ToLocalChecked(), IsTrialGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("startDate").ToLocalChecked(), StartDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trialTimeRemaining").ToLocalChecked(), TrialTimeRemainingGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreCollectionData").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreCollectionData(::Windows::Services::Store::StoreCollectionData^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreCollectionData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreCollectionData^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreCollectionData *wrapperInstance = new StoreCollectionData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreCollectionData^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreCollectionData^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreCollectionData(winRtInstance));
    }





    static void AcquiredDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->AcquiredDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CampaignIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CampaignId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DeveloperOfferIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DeveloperOfferId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void EndDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->EndDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsTrialGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        bool result = wrapper->_instance->IsTrial;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StartDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->StartDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrialTimeRemainingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCollectionData^>(info.This())) {
        return;
      }

      StoreCollectionData *wrapper = StoreCollectionData::Unwrap<StoreCollectionData>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->TrialTimeRemaining;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreCollectionData^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreCollectionData(::Windows::Services::Store::StoreCollectionData^ wintRtInstance);
      friend ::Windows::Services::Store::StoreCollectionData^ UnwrapStoreCollectionData(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreCollectionData::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreCollectionData(::Windows::Services::Store::StoreCollectionData^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreCollectionData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreCollectionData^ UnwrapStoreCollectionData(Local<Value> value) {
     return StoreCollectionData::Unwrap<StoreCollectionData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreCollectionData(Local<Object> exports) {
    StoreCollectionData::Init(exports);
  }

  class StoreSubscriptionInfo : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreSubscriptionInfo").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("billingPeriod").ToLocalChecked(), BillingPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("billingPeriodUnit").ToLocalChecked(), BillingPeriodUnitGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hasTrialPeriod").ToLocalChecked(), HasTrialPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trialPeriod").ToLocalChecked(), TrialPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trialPeriodUnit").ToLocalChecked(), TrialPeriodUnitGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreSubscriptionInfo").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreSubscriptionInfo(::Windows::Services::Store::StoreSubscriptionInfo^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreSubscriptionInfo^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreSubscriptionInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreSubscriptionInfo *wrapperInstance = new StoreSubscriptionInfo(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreSubscriptionInfo^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreSubscriptionInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreSubscriptionInfo(winRtInstance));
    }





    static void BillingPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info.This())) {
        return;
      }

      StoreSubscriptionInfo *wrapper = StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(info.This());

      try  {
        unsigned int result = wrapper->_instance->BillingPeriod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BillingPeriodUnitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info.This())) {
        return;
      }

      StoreSubscriptionInfo *wrapper = StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(info.This());

      try  {
        ::Windows::Services::Store::StoreDurationUnit result = wrapper->_instance->BillingPeriodUnit;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HasTrialPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info.This())) {
        return;
      }

      StoreSubscriptionInfo *wrapper = StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(info.This());

      try  {
        bool result = wrapper->_instance->HasTrialPeriod;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrialPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info.This())) {
        return;
      }

      StoreSubscriptionInfo *wrapper = StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(info.This());

      try  {
        unsigned int result = wrapper->_instance->TrialPeriod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrialPeriodUnitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSubscriptionInfo^>(info.This())) {
        return;
      }

      StoreSubscriptionInfo *wrapper = StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(info.This());

      try  {
        ::Windows::Services::Store::StoreDurationUnit result = wrapper->_instance->TrialPeriodUnit;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreSubscriptionInfo^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreSubscriptionInfo(::Windows::Services::Store::StoreSubscriptionInfo^ wintRtInstance);
      friend ::Windows::Services::Store::StoreSubscriptionInfo^ UnwrapStoreSubscriptionInfo(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreSubscriptionInfo::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreSubscriptionInfo(::Windows::Services::Store::StoreSubscriptionInfo^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreSubscriptionInfo::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreSubscriptionInfo^ UnwrapStoreSubscriptionInfo(Local<Value> value) {
     return StoreSubscriptionInfo::Unwrap<StoreSubscriptionInfo>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreSubscriptionInfo(Local<Object> exports) {
    StoreSubscriptionInfo::Init(exports);
  }

  class StoreContext : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreContext").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getCustomerPurchaseIdAsync", GetCustomerPurchaseIdAsync);
            Nan::SetPrototypeMethod(localRef, "getCustomerCollectionsIdAsync", GetCustomerCollectionsIdAsync);
            Nan::SetPrototypeMethod(localRef, "getAppLicenseAsync", GetAppLicenseAsync);
            Nan::SetPrototypeMethod(localRef, "getStoreProductForCurrentAppAsync", GetStoreProductForCurrentAppAsync);
            Nan::SetPrototypeMethod(localRef, "getStoreProductsAsync", GetStoreProductsAsync);
            Nan::SetPrototypeMethod(localRef, "getAssociatedStoreProductsAsync", GetAssociatedStoreProductsAsync);
            Nan::SetPrototypeMethod(localRef, "getAssociatedStoreProductsWithPagingAsync", GetAssociatedStoreProductsWithPagingAsync);
            Nan::SetPrototypeMethod(localRef, "getUserCollectionAsync", GetUserCollectionAsync);
            Nan::SetPrototypeMethod(localRef, "getUserCollectionWithPagingAsync", GetUserCollectionWithPagingAsync);
            Nan::SetPrototypeMethod(localRef, "reportConsumableFulfillmentAsync", ReportConsumableFulfillmentAsync);
            Nan::SetPrototypeMethod(localRef, "getConsumableBalanceRemainingAsync", GetConsumableBalanceRemainingAsync);
            Nan::SetPrototypeMethod(localRef, "acquireStoreLicenseForOptionalPackageAsync", AcquireStoreLicenseForOptionalPackageAsync);
            Nan::SetPrototypeMethod(localRef, "requestPurchaseAsync", RequestPurchaseAsync);
            Nan::SetPrototypeMethod(localRef, "getAppAndOptionalStorePackageUpdatesAsync", GetAppAndOptionalStorePackageUpdatesAsync);
            Nan::SetPrototypeMethod(localRef, "requestDownloadStorePackageUpdatesAsync", RequestDownloadStorePackageUpdatesAsync);
            Nan::SetPrototypeMethod(localRef, "requestDownloadAndInstallStorePackageUpdatesAsync", RequestDownloadAndInstallStorePackageUpdatesAsync);
            Nan::SetPrototypeMethod(localRef, "requestDownloadAndInstallStorePackagesAsync", RequestDownloadAndInstallStorePackagesAsync);
            Nan::SetPrototypeMethod(localRef, "findStoreProductForPackageAsync", FindStoreProductForPackageAsync);
            Nan::SetPrototypeMethod(localRef, "trySilentDownloadStorePackageUpdatesAsync", TrySilentDownloadStorePackageUpdatesAsync);
            Nan::SetPrototypeMethod(localRef, "trySilentDownloadAndInstallStorePackageUpdatesAsync", TrySilentDownloadAndInstallStorePackageUpdatesAsync);
            Nan::SetPrototypeMethod(localRef, "canAcquireStoreLicenseForOptionalPackageAsync", CanAcquireStoreLicenseForOptionalPackageAsync);
            Nan::SetPrototypeMethod(localRef, "canAcquireStoreLicenseAsync", CanAcquireStoreLicenseAsync);
            Nan::SetPrototypeMethod(localRef, "getAssociatedStoreQueueItemsAsync", GetAssociatedStoreQueueItemsAsync);
            Nan::SetPrototypeMethod(localRef, "getStoreQueueItemsAsync", GetStoreQueueItemsAsync);
            Nan::SetPrototypeMethod(localRef, "downloadAndInstallStorePackagesAsync", DownloadAndInstallStorePackagesAsync);
            Nan::SetPrototypeMethod(localRef, "requestUninstallStorePackageAsync", RequestUninstallStorePackageAsync);
            Nan::SetPrototypeMethod(localRef, "requestUninstallStorePackageByStoreIdAsync", RequestUninstallStorePackageByStoreIdAsync);
            Nan::SetPrototypeMethod(localRef, "uninstallStorePackageAsync", UninstallStorePackageAsync);
            Nan::SetPrototypeMethod(localRef, "uninstallStorePackageByStoreIdAsync", UninstallStorePackageByStoreIdAsync);
          

          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("user").ToLocalChecked(), UserGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canSilentlyDownloadStorePackageUpdates").ToLocalChecked(), CanSilentlyDownloadStorePackageUpdatesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getDefault", GetDefault);
        Nan::SetMethod(constructor, "getForUser", GetForUser);


        Nan::Set(exports, Nan::New<String>("StoreContext").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreContext(::Windows::Services::Store::StoreContext^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreContext^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreContext^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreContext *wrapperInstance = new StoreContext(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreContext^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreContext^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreContext(winRtInstance));
    }

    static void GetCustomerPurchaseIdAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Platform::String^>^ op;


      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->GetCustomerPurchaseIdAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Platform::String^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::NewString(result->Data());
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetCustomerCollectionsIdAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Platform::String^>^ op;


      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->GetCustomerCollectionsIdAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Platform::String^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::NewString(result->Data());
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetAppLicenseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreAppLicense^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetAppLicenseAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreAppLicense^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreAppLicense(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetStoreProductForCurrentAppAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductResult^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetStoreProductForCurrentAppAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetStoreProductsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductQueryResult^>^ op;


      if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          
          op = wrapper->_instance->GetStoreProductsAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductOptions^>(info[2]))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Services::Store::StoreProductOptions^ arg2 = UnwrapStoreProductOptions(info[2]);
          
          op = wrapper->_instance->GetStoreProductsAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetAssociatedStoreProductsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductQueryResult^>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->GetAssociatedStoreProductsAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetAssociatedStoreProductsWithPagingAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductPagedQueryResult^>^ op;


      if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetAssociatedStoreProductsWithPagingAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductPagedQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductPagedQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetUserCollectionAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductQueryResult^>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->GetUserCollectionAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetUserCollectionWithPagingAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductPagedQueryResult^>^ op;


      if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetUserCollectionWithPagingAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductPagedQueryResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductPagedQueryResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void ReportConsumableFulfillmentAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreConsumableResult^>^ op;


      if (info.Length() == 4
        && info[0]->IsString()
        && info[1]->IsUint32()
        && NodeRT::Utils::IsGuid(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          
          op = wrapper->_instance->ReportConsumableFulfillmentAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreConsumableResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreConsumableResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetConsumableBalanceRemainingAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreConsumableResult^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetConsumableBalanceRemainingAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreConsumableResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreConsumableResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void AcquireStoreLicenseForOptionalPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreAcquireLicenseResult^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
      {
        try
        {
          ::Windows::ApplicationModel::Package^ arg0 = dynamic_cast<::Windows::ApplicationModel::Package^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->AcquireStoreLicenseForOptionalPackageAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreAcquireLicenseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreAcquireLicenseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestPurchaseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StorePurchaseResult^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->RequestPurchaseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePurchaseProperties^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Services::Store::StorePurchaseProperties^ arg1 = UnwrapStorePurchaseProperties(info[1]);
          
          op = wrapper->_instance->RequestPurchaseAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePurchaseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePurchaseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetAppAndOptionalStorePackageUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StorePackageUpdate^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetAppAndOptionalStorePackageUpdatesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StorePackageUpdate^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StorePackageUpdate^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StorePackageUpdate^ val) -> Local<Value> {
              return WrapStorePackageUpdate(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdate^ {
              return UnwrapStorePackageUpdate(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestDownloadStorePackageUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Services::Store::StorePackageUpdate^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdate^ {
                   return UnwrapStorePackageUpdate(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->RequestDownloadStorePackageUpdatesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestDownloadAndInstallStorePackageUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Services::Store::StorePackageUpdate^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdate^ {
                   return UnwrapStorePackageUpdate(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->RequestDownloadAndInstallStorePackageUpdatesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestDownloadAndInstallStorePackagesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->RequestDownloadAndInstallStorePackagesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageInstallOptions^>(info[1]))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Services::Store::StorePackageInstallOptions^ arg1 = UnwrapStorePackageInstallOptions(info[1]);
          
          op = wrapper->_instance->RequestDownloadAndInstallStorePackagesAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void FindStoreProductForPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreProductResult^>^ op;


      if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[1]))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::ApplicationModel::Package^ arg1 = dynamic_cast<::Windows::ApplicationModel::Package^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          op = wrapper->_instance->FindStoreProductForPackageAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreProductResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreProductResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void TrySilentDownloadStorePackageUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Services::Store::StorePackageUpdate^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdate^ {
                   return UnwrapStorePackageUpdate(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->TrySilentDownloadStorePackageUpdatesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void TrySilentDownloadAndInstallStorePackageUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Services::Store::StorePackageUpdate^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdate^ {
                   return UnwrapStorePackageUpdate(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Services::Store::StorePackageUpdate^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->TrySilentDownloadAndInstallStorePackageUpdatesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CanAcquireStoreLicenseForOptionalPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreCanAcquireLicenseResult^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
      {
        try
        {
          ::Windows::ApplicationModel::Package^ arg0 = dynamic_cast<::Windows::ApplicationModel::Package^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->CanAcquireStoreLicenseForOptionalPackageAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreCanAcquireLicenseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreCanAcquireLicenseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CanAcquireStoreLicenseAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreCanAcquireLicenseResult^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->CanAcquireStoreLicenseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreCanAcquireLicenseResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreCanAcquireLicenseResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetAssociatedStoreQueueItemsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreQueueItem^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetAssociatedStoreQueueItemsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreQueueItem^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreQueueItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreQueueItem^ val) -> Local<Value> {
              return WrapStoreQueueItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreQueueItem^ {
              return UnwrapStoreQueueItem(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetStoreQueueItemsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreQueueItem^>^>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->GetStoreQueueItemsAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreQueueItem^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreQueueItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreQueueItem^ val) -> Local<Value> {
              return WrapStoreQueueItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreQueueItem^ {
              return UnwrapStoreQueueItem(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void DownloadAndInstallStorePackagesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Services::Store::StorePackageUpdateResult^, ::Windows::Services::Store::StorePackageUpdateStatus>^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->DownloadAndInstallStorePackagesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StorePackageUpdateResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorePackageUpdateResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestUninstallStorePackageAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreUninstallStorePackageResult^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
      {
        try
        {
          ::Windows::ApplicationModel::Package^ arg0 = dynamic_cast<::Windows::ApplicationModel::Package^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->RequestUninstallStorePackageAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreUninstallStorePackageResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreUninstallStorePackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestUninstallStorePackageByStoreIdAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreUninstallStorePackageResult^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->RequestUninstallStorePackageByStoreIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreUninstallStorePackageResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreUninstallStorePackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void UninstallStorePackageAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreUninstallStorePackageResult^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
      {
        try
        {
          ::Windows::ApplicationModel::Package^ arg0 = dynamic_cast<::Windows::ApplicationModel::Package^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->UninstallStorePackageAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreUninstallStorePackageResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreUninstallStorePackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void UninstallStorePackageByStoreIdAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreUninstallStorePackageResult^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->UninstallStorePackageByStoreIdAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreUninstallStorePackageResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreUninstallStorePackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void GetDefault(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Services::Store::StoreContext^ result;
          result = ::Windows::Services::Store::StoreContext::GetDefault();
          info.GetReturnValue().Set(WrapStoreContext(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Services::Store::StoreContext^ result;
          result = ::Windows::Services::Store::StoreContext::GetForUser(arg0);
          info.GetReturnValue().Set(WrapStoreContext(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void UserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      try  {
        ::Windows::System::User^ result = wrapper->_instance->User;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.System", "User", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanSilentlyDownloadStorePackageUpdatesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This())) {
        return;
      }

      StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());

      try  {
        bool result = wrapper->_instance->CanSilentlyDownloadStorePackageUpdates;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"offlineLicensesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->OfflineLicensesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Services::Store::StoreContext^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Services::Store::StoreContext^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapStoreContext(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"offlineLicensesChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"offlineLicensesChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          StoreContext *wrapper = StoreContext::Unwrap<StoreContext>(info.This());
          wrapper->_instance->OfflineLicensesChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Services::Store::StoreContext^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreContext(::Windows::Services::Store::StoreContext^ wintRtInstance);
      friend ::Windows::Services::Store::StoreContext^ UnwrapStoreContext(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreContext::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreContext(::Windows::Services::Store::StoreContext^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreContext::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreContext^ UnwrapStoreContext(Local<Value> value) {
     return StoreContext::Unwrap<StoreContext>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreContext(Local<Object> exports) {
    StoreContext::Init(exports);
  }

  class StoreSendRequestResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreSendRequestResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("response").ToLocalChecked(), ResponseGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("httpStatusCode").ToLocalChecked(), HttpStatusCodeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreSendRequestResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreSendRequestResult(::Windows::Services::Store::StoreSendRequestResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreSendRequestResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSendRequestResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreSendRequestResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreSendRequestResult *wrapperInstance = new StoreSendRequestResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSendRequestResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreSendRequestResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreSendRequestResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreSendRequestResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSendRequestResult^>(info.This())) {
        return;
      }

      StoreSendRequestResult *wrapper = StoreSendRequestResult::Unwrap<StoreSendRequestResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ResponseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSendRequestResult^>(info.This())) {
        return;
      }

      StoreSendRequestResult *wrapper = StoreSendRequestResult::Unwrap<StoreSendRequestResult>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Response;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HttpStatusCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreSendRequestResult^>(info.This())) {
        return;
      }

      StoreSendRequestResult *wrapper = StoreSendRequestResult::Unwrap<StoreSendRequestResult>(info.This());

      try  {
        ::Windows::Web::Http::HttpStatusCode result = wrapper->_instance->HttpStatusCode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreSendRequestResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreSendRequestResult(::Windows::Services::Store::StoreSendRequestResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreSendRequestResult^ UnwrapStoreSendRequestResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreSendRequestResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreSendRequestResult(::Windows::Services::Store::StoreSendRequestResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreSendRequestResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreSendRequestResult^ UnwrapStoreSendRequestResult(Local<Value> value) {
     return StoreSendRequestResult::Unwrap<StoreSendRequestResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreSendRequestResult(Local<Object> exports) {
    StoreSendRequestResult::Init(exports);
  }

  class StoreAppLicense : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreAppLicense").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("addOnLicenses").ToLocalChecked(), AddOnLicensesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationDate").ToLocalChecked(), ExpirationDateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedJsonData").ToLocalChecked(), ExtendedJsonDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isActive").ToLocalChecked(), IsActiveGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isTrial").ToLocalChecked(), IsTrialGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isTrialOwnedByThisUser").ToLocalChecked(), IsTrialOwnedByThisUserGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("skuStoreId").ToLocalChecked(), SkuStoreIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trialTimeRemaining").ToLocalChecked(), TrialTimeRemainingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trialUniqueId").ToLocalChecked(), TrialUniqueIdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreAppLicense").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreAppLicense(::Windows::Services::Store::StoreAppLicense^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreAppLicense^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreAppLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreAppLicense *wrapperInstance = new StoreAppLicense(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreAppLicense^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreAppLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreAppLicense(winRtInstance));
    }





    static void AddOnLicensesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Windows::Services::Store::StoreLicense^>^ result = wrapper->_instance->AddOnLicenses;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Windows::Services::Store::StoreLicense^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Windows::Services::Store::StoreLicense^ val) -> Local<Value> {
              return WrapStoreLicense(val);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExpirationDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->ExpirationDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedJsonDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ExtendedJsonData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsActiveGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        bool result = wrapper->_instance->IsActive;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsTrialGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        bool result = wrapper->_instance->IsTrial;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsTrialOwnedByThisUserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        bool result = wrapper->_instance->IsTrialOwnedByThisUser;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SkuStoreIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SkuStoreId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrialTimeRemainingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->TrialTimeRemaining;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrialUniqueIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAppLicense^>(info.This())) {
        return;
      }

      StoreAppLicense *wrapper = StoreAppLicense::Unwrap<StoreAppLicense>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->TrialUniqueId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreAppLicense^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreAppLicense(::Windows::Services::Store::StoreAppLicense^ wintRtInstance);
      friend ::Windows::Services::Store::StoreAppLicense^ UnwrapStoreAppLicense(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreAppLicense::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreAppLicense(::Windows::Services::Store::StoreAppLicense^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreAppLicense::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreAppLicense^ UnwrapStoreAppLicense(Local<Value> value) {
     return StoreAppLicense::Unwrap<StoreAppLicense>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreAppLicense(Local<Object> exports) {
    StoreAppLicense::Init(exports);
  }

  class StoreProductResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreProductResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("product").ToLocalChecked(), ProductGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreProductResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreProductResult(::Windows::Services::Store::StoreProductResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreProductResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreProductResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreProductResult *wrapperInstance = new StoreProductResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreProductResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreProductResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreProductResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductResult^>(info.This())) {
        return;
      }

      StoreProductResult *wrapper = StoreProductResult::Unwrap<StoreProductResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProductGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductResult^>(info.This())) {
        return;
      }

      StoreProductResult *wrapper = StoreProductResult::Unwrap<StoreProductResult>(info.This());

      try  {
        ::Windows::Services::Store::StoreProduct^ result = wrapper->_instance->Product;
        info.GetReturnValue().Set(WrapStoreProduct(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreProductResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreProductResult(::Windows::Services::Store::StoreProductResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreProductResult^ UnwrapStoreProductResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreProductResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreProductResult(::Windows::Services::Store::StoreProductResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreProductResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreProductResult^ UnwrapStoreProductResult(Local<Value> value) {
     return StoreProductResult::Unwrap<StoreProductResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreProductResult(Local<Object> exports) {
    StoreProductResult::Init(exports);
  }

  class StoreProductQueryResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreProductQueryResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("products").ToLocalChecked(), ProductsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreProductQueryResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreProductQueryResult(::Windows::Services::Store::StoreProductQueryResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreProductQueryResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductQueryResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreProductQueryResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreProductQueryResult *wrapperInstance = new StoreProductQueryResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductQueryResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreProductQueryResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreProductQueryResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreProductQueryResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductQueryResult^>(info.This())) {
        return;
      }

      StoreProductQueryResult *wrapper = StoreProductQueryResult::Unwrap<StoreProductQueryResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProductsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductQueryResult^>(info.This())) {
        return;
      }

      StoreProductQueryResult *wrapper = StoreProductQueryResult::Unwrap<StoreProductQueryResult>(info.This());

      try  {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Windows::Services::Store::StoreProduct^>^ result = wrapper->_instance->Products;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Windows::Services::Store::StoreProduct^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Windows::Services::Store::StoreProduct^ val) -> Local<Value> {
              return WrapStoreProduct(val);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreProductQueryResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreProductQueryResult(::Windows::Services::Store::StoreProductQueryResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreProductQueryResult^ UnwrapStoreProductQueryResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreProductQueryResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreProductQueryResult(::Windows::Services::Store::StoreProductQueryResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreProductQueryResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreProductQueryResult^ UnwrapStoreProductQueryResult(Local<Value> value) {
     return StoreProductQueryResult::Unwrap<StoreProductQueryResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreProductQueryResult(Local<Object> exports) {
    StoreProductQueryResult::Init(exports);
  }

  class StoreConsumableResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreConsumableResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("balanceRemaining").ToLocalChecked(), BalanceRemainingGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trackingId").ToLocalChecked(), TrackingIdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreConsumableResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreConsumableResult(::Windows::Services::Store::StoreConsumableResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreConsumableResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreConsumableResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreConsumableResult *wrapperInstance = new StoreConsumableResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreConsumableResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreConsumableResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreConsumableResult(winRtInstance));
    }





    static void BalanceRemainingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info.This())) {
        return;
      }

      StoreConsumableResult *wrapper = StoreConsumableResult::Unwrap<StoreConsumableResult>(info.This());

      try  {
        unsigned int result = wrapper->_instance->BalanceRemaining;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info.This())) {
        return;
      }

      StoreConsumableResult *wrapper = StoreConsumableResult::Unwrap<StoreConsumableResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info.This())) {
        return;
      }

      StoreConsumableResult *wrapper = StoreConsumableResult::Unwrap<StoreConsumableResult>(info.This());

      try  {
        ::Windows::Services::Store::StoreConsumableStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrackingIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreConsumableResult^>(info.This())) {
        return;
      }

      StoreConsumableResult *wrapper = StoreConsumableResult::Unwrap<StoreConsumableResult>(info.This());

      try  {
        ::Platform::Guid result = wrapper->_instance->TrackingId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreConsumableResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreConsumableResult(::Windows::Services::Store::StoreConsumableResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreConsumableResult^ UnwrapStoreConsumableResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreConsumableResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreConsumableResult(::Windows::Services::Store::StoreConsumableResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreConsumableResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreConsumableResult^ UnwrapStoreConsumableResult(Local<Value> value) {
     return StoreConsumableResult::Unwrap<StoreConsumableResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreConsumableResult(Local<Object> exports) {
    StoreConsumableResult::Init(exports);
  }

  class StoreAcquireLicenseResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreAcquireLicenseResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storePackageLicense").ToLocalChecked(), StorePackageLicenseGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreAcquireLicenseResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreAcquireLicenseResult(::Windows::Services::Store::StoreAcquireLicenseResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreAcquireLicenseResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAcquireLicenseResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreAcquireLicenseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreAcquireLicenseResult *wrapperInstance = new StoreAcquireLicenseResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAcquireLicenseResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreAcquireLicenseResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreAcquireLicenseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreAcquireLicenseResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAcquireLicenseResult^>(info.This())) {
        return;
      }

      StoreAcquireLicenseResult *wrapper = StoreAcquireLicenseResult::Unwrap<StoreAcquireLicenseResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StorePackageLicenseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreAcquireLicenseResult^>(info.This())) {
        return;
      }

      StoreAcquireLicenseResult *wrapper = StoreAcquireLicenseResult::Unwrap<StoreAcquireLicenseResult>(info.This());

      try  {
        ::Windows::Services::Store::StorePackageLicense^ result = wrapper->_instance->StorePackageLicense;
        info.GetReturnValue().Set(WrapStorePackageLicense(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreAcquireLicenseResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreAcquireLicenseResult(::Windows::Services::Store::StoreAcquireLicenseResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreAcquireLicenseResult^ UnwrapStoreAcquireLicenseResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreAcquireLicenseResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreAcquireLicenseResult(::Windows::Services::Store::StoreAcquireLicenseResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreAcquireLicenseResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreAcquireLicenseResult^ UnwrapStoreAcquireLicenseResult(Local<Value> value) {
     return StoreAcquireLicenseResult::Unwrap<StoreAcquireLicenseResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreAcquireLicenseResult(Local<Object> exports) {
    StoreAcquireLicenseResult::Init(exports);
  }

  class StorePackageUpdate : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePackageUpdate").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mandatory").ToLocalChecked(), MandatoryGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePackageUpdate").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePackageUpdate(::Windows::Services::Store::StorePackageUpdate^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePackageUpdate^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePackageUpdate^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePackageUpdate *wrapperInstance = new StorePackageUpdate(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePackageUpdate^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePackageUpdate^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePackageUpdate(winRtInstance));
    }





    static void MandatoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(info.This())) {
        return;
      }

      StorePackageUpdate *wrapper = StorePackageUpdate::Unwrap<StorePackageUpdate>(info.This());

      try  {
        bool result = wrapper->_instance->Mandatory;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdate^>(info.This())) {
        return;
      }

      StorePackageUpdate *wrapper = StorePackageUpdate::Unwrap<StorePackageUpdate>(info.This());

      try  {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel", "Package", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StorePackageUpdate^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePackageUpdate(::Windows::Services::Store::StorePackageUpdate^ wintRtInstance);
      friend ::Windows::Services::Store::StorePackageUpdate^ UnwrapStorePackageUpdate(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePackageUpdate::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePackageUpdate(::Windows::Services::Store::StorePackageUpdate^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePackageUpdate::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePackageUpdate^ UnwrapStorePackageUpdate(Local<Value> value) {
     return StorePackageUpdate::Unwrap<StorePackageUpdate>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePackageUpdate(Local<Object> exports) {
    StorePackageUpdate::Init(exports);
  }

  class StorePackageUpdateResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePackageUpdateResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("overallState").ToLocalChecked(), OverallStateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storePackageUpdateStatuses").ToLocalChecked(), StorePackageUpdateStatusesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("storeQueueItems").ToLocalChecked(), StoreQueueItemsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePackageUpdateResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePackageUpdateResult(::Windows::Services::Store::StorePackageUpdateResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePackageUpdateResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdateResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePackageUpdateResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePackageUpdateResult *wrapperInstance = new StorePackageUpdateResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdateResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePackageUpdateResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePackageUpdateResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePackageUpdateResult(winRtInstance));
    }





    static void OverallStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdateResult^>(info.This())) {
        return;
      }

      StorePackageUpdateResult *wrapper = StorePackageUpdateResult::Unwrap<StorePackageUpdateResult>(info.This());

      try  {
        ::Windows::Services::Store::StorePackageUpdateState result = wrapper->_instance->OverallState;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StorePackageUpdateStatusesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdateResult^>(info.This())) {
        return;
      }

      StorePackageUpdateResult *wrapper = StorePackageUpdateResult::Unwrap<StorePackageUpdateResult>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StorePackageUpdateStatus>^ result = wrapper->_instance->StorePackageUpdateStatuses;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StorePackageUpdateStatus>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StorePackageUpdateStatus val) -> Local<Value> {
              return StorePackageUpdateStatusToJsObject(val);
            },
            [](Local<Value> value) -> bool {
              return IsStorePackageUpdateStatusJsObject(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StorePackageUpdateStatus {
              return StorePackageUpdateStatusFromJsObject(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StoreQueueItemsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageUpdateResult^>(info.This())) {
        return;
      }

      StorePackageUpdateResult *wrapper = StorePackageUpdateResult::Unwrap<StorePackageUpdateResult>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Services::Store::StoreQueueItem^>^ result = wrapper->_instance->StoreQueueItems;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Services::Store::StoreQueueItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Services::Store::StoreQueueItem^ val) -> Local<Value> {
              return WrapStoreQueueItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Services::Store::StoreQueueItem^ {
              return UnwrapStoreQueueItem(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StorePackageUpdateResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePackageUpdateResult(::Windows::Services::Store::StorePackageUpdateResult^ wintRtInstance);
      friend ::Windows::Services::Store::StorePackageUpdateResult^ UnwrapStorePackageUpdateResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePackageUpdateResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePackageUpdateResult(::Windows::Services::Store::StorePackageUpdateResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePackageUpdateResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePackageUpdateResult^ UnwrapStorePackageUpdateResult(Local<Value> value) {
     return StorePackageUpdateResult::Unwrap<StorePackageUpdateResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePackageUpdateResult(Local<Object> exports) {
    StorePackageUpdateResult::Init(exports);
  }

  class StoreCanAcquireLicenseResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreCanAcquireLicenseResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("licensableSku").ToLocalChecked(), LicensableSkuGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreCanAcquireLicenseResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreCanAcquireLicenseResult(::Windows::Services::Store::StoreCanAcquireLicenseResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreCanAcquireLicenseResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCanAcquireLicenseResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreCanAcquireLicenseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreCanAcquireLicenseResult *wrapperInstance = new StoreCanAcquireLicenseResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCanAcquireLicenseResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreCanAcquireLicenseResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreCanAcquireLicenseResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreCanAcquireLicenseResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCanAcquireLicenseResult^>(info.This())) {
        return;
      }

      StoreCanAcquireLicenseResult *wrapper = StoreCanAcquireLicenseResult::Unwrap<StoreCanAcquireLicenseResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LicensableSkuGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCanAcquireLicenseResult^>(info.This())) {
        return;
      }

      StoreCanAcquireLicenseResult *wrapper = StoreCanAcquireLicenseResult::Unwrap<StoreCanAcquireLicenseResult>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LicensableSku;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreCanAcquireLicenseResult^>(info.This())) {
        return;
      }

      StoreCanAcquireLicenseResult *wrapper = StoreCanAcquireLicenseResult::Unwrap<StoreCanAcquireLicenseResult>(info.This());

      try  {
        ::Windows::Services::Store::StoreCanLicenseStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreCanAcquireLicenseResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreCanAcquireLicenseResult(::Windows::Services::Store::StoreCanAcquireLicenseResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreCanAcquireLicenseResult^ UnwrapStoreCanAcquireLicenseResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreCanAcquireLicenseResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreCanAcquireLicenseResult(::Windows::Services::Store::StoreCanAcquireLicenseResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreCanAcquireLicenseResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreCanAcquireLicenseResult^ UnwrapStoreCanAcquireLicenseResult(Local<Value> value) {
     return StoreCanAcquireLicenseResult::Unwrap<StoreCanAcquireLicenseResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreCanAcquireLicenseResult(Local<Object> exports) {
    StoreCanAcquireLicenseResult::Init(exports);
  }

  class StoreProductOptions : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreProductOptions").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("actionFilters").ToLocalChecked(), ActionFiltersGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreProductOptions").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreProductOptions(::Windows::Services::Store::StoreProductOptions^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreProductOptions^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductOptions^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreProductOptions^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Services::Store::StoreProductOptions();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreProductOptions *wrapperInstance = new StoreProductOptions(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductOptions^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreProductOptions^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreProductOptions^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreProductOptions(winRtInstance));
    }





    static void ActionFiltersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreProductOptions^>(info.This())) {
        return;
      }

      StoreProductOptions *wrapper = StoreProductOptions::Unwrap<StoreProductOptions>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result = wrapper->_instance->ActionFilters;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreProductOptions^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreProductOptions(::Windows::Services::Store::StoreProductOptions^ wintRtInstance);
      friend ::Windows::Services::Store::StoreProductOptions^ UnwrapStoreProductOptions(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreProductOptions::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreProductOptions(::Windows::Services::Store::StoreProductOptions^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreProductOptions::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreProductOptions^ UnwrapStoreProductOptions(Local<Value> value) {
     return StoreProductOptions::Unwrap<StoreProductOptions>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreProductOptions(Local<Object> exports) {
    StoreProductOptions::Init(exports);
  }

  class StoreQueueItem : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreQueueItem").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getCurrentStatus", GetCurrentStatus);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("installKind").ToLocalChecked(), InstallKindGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packageFamilyName").ToLocalChecked(), PackageFamilyNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("productId").ToLocalChecked(), ProductIdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreQueueItem").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreQueueItem(::Windows::Services::Store::StoreQueueItem^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreQueueItem^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreQueueItem^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreQueueItem *wrapperInstance = new StoreQueueItem(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreQueueItem^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreQueueItem^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreQueueItem(winRtInstance));
    }


    static void GetCurrentStatus(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This())) {
        return;
      }

      StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Services::Store::StoreQueueItemStatus^ result;
          result = wrapper->_instance->GetCurrentStatus();
          info.GetReturnValue().Set(WrapStoreQueueItemStatus(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void InstallKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This())) {
        return;
      }

      StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());

      try  {
        ::Windows::Services::Store::StoreQueueItemKind result = wrapper->_instance->InstallKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PackageFamilyNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This())) {
        return;
      }

      StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PackageFamilyName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProductIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This())) {
        return;
      }

      StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ProductId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"completed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Completed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Services::Store::StoreQueueItem^, ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^>(
            [callbackObjPtr](::Windows::Services::Store::StoreQueueItem^ arg0, ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapStoreQueueItem(arg0);
                  wrappedArg1 = WrapStoreQueueItemCompletedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->StatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Services::Store::StoreQueueItem^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Services::Store::StoreQueueItem^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapStoreQueueItem(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"completed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"completed", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());
          wrapper->_instance->Completed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"statusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItem^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          StoreQueueItem *wrapper = StoreQueueItem::Unwrap<StoreQueueItem>(info.This());
          wrapper->_instance->StatusChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Services::Store::StoreQueueItem^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreQueueItem(::Windows::Services::Store::StoreQueueItem^ wintRtInstance);
      friend ::Windows::Services::Store::StoreQueueItem^ UnwrapStoreQueueItem(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreQueueItem::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreQueueItem(::Windows::Services::Store::StoreQueueItem^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreQueueItem::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreQueueItem^ UnwrapStoreQueueItem(Local<Value> value) {
     return StoreQueueItem::Unwrap<StoreQueueItem>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreQueueItem(Local<Object> exports) {
    StoreQueueItem::Init(exports);
  }

  class StorePackageInstallOptions : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePackageInstallOptions").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("allowForcedAppRestart").ToLocalChecked(), AllowForcedAppRestartGetter, AllowForcedAppRestartSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePackageInstallOptions").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePackageInstallOptions(::Windows::Services::Store::StorePackageInstallOptions^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePackageInstallOptions^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageInstallOptions^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePackageInstallOptions^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Services::Store::StorePackageInstallOptions();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePackageInstallOptions *wrapperInstance = new StorePackageInstallOptions(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageInstallOptions^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePackageInstallOptions^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePackageInstallOptions^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePackageInstallOptions(winRtInstance));
    }





    static void AllowForcedAppRestartGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageInstallOptions^>(info.This())) {
        return;
      }

      StorePackageInstallOptions *wrapper = StorePackageInstallOptions::Unwrap<StorePackageInstallOptions>(info.This());

      try  {
        bool result = wrapper->_instance->AllowForcedAppRestart;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AllowForcedAppRestartSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageInstallOptions^>(info.This())) {
        return;
      }

      StorePackageInstallOptions *wrapper = StorePackageInstallOptions::Unwrap<StorePackageInstallOptions>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->AllowForcedAppRestart = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Services::Store::StorePackageInstallOptions^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePackageInstallOptions(::Windows::Services::Store::StorePackageInstallOptions^ wintRtInstance);
      friend ::Windows::Services::Store::StorePackageInstallOptions^ UnwrapStorePackageInstallOptions(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePackageInstallOptions::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePackageInstallOptions(::Windows::Services::Store::StorePackageInstallOptions^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePackageInstallOptions::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePackageInstallOptions^ UnwrapStorePackageInstallOptions(Local<Value> value) {
     return StorePackageInstallOptions::Unwrap<StorePackageInstallOptions>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePackageInstallOptions(Local<Object> exports) {
    StorePackageInstallOptions::Init(exports);
  }

  class StoreUninstallStorePackageResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreUninstallStorePackageResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreUninstallStorePackageResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreUninstallStorePackageResult(::Windows::Services::Store::StoreUninstallStorePackageResult^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreUninstallStorePackageResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreUninstallStorePackageResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreUninstallStorePackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreUninstallStorePackageResult *wrapperInstance = new StoreUninstallStorePackageResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreUninstallStorePackageResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreUninstallStorePackageResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreUninstallStorePackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreUninstallStorePackageResult(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreUninstallStorePackageResult^>(info.This())) {
        return;
      }

      StoreUninstallStorePackageResult *wrapper = StoreUninstallStorePackageResult::Unwrap<StoreUninstallStorePackageResult>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreUninstallStorePackageResult^>(info.This())) {
        return;
      }

      StoreUninstallStorePackageResult *wrapper = StoreUninstallStorePackageResult::Unwrap<StoreUninstallStorePackageResult>(info.This());

      try  {
        ::Windows::Services::Store::StoreUninstallStorePackageStatus result = wrapper->_instance->Status;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreUninstallStorePackageResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreUninstallStorePackageResult(::Windows::Services::Store::StoreUninstallStorePackageResult^ wintRtInstance);
      friend ::Windows::Services::Store::StoreUninstallStorePackageResult^ UnwrapStoreUninstallStorePackageResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreUninstallStorePackageResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreUninstallStorePackageResult(::Windows::Services::Store::StoreUninstallStorePackageResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreUninstallStorePackageResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreUninstallStorePackageResult^ UnwrapStoreUninstallStorePackageResult(Local<Value> value) {
     return StoreUninstallStorePackageResult::Unwrap<StoreUninstallStorePackageResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreUninstallStorePackageResult(Local<Object> exports) {
    StoreUninstallStorePackageResult::Init(exports);
  }

  class StoreQueueItemStatus : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreQueueItemStatus").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packageInstallExtendedState").ToLocalChecked(), PackageInstallExtendedStateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packageInstallState").ToLocalChecked(), PackageInstallStateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("updateStatus").ToLocalChecked(), UpdateStatusGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreQueueItemStatus").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreQueueItemStatus(::Windows::Services::Store::StoreQueueItemStatus^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreQueueItemStatus^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreQueueItemStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreQueueItemStatus *wrapperInstance = new StoreQueueItemStatus(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreQueueItemStatus^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreQueueItemStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreQueueItemStatus(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info.This())) {
        return;
      }

      StoreQueueItemStatus *wrapper = StoreQueueItemStatus::Unwrap<StoreQueueItemStatus>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PackageInstallExtendedStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info.This())) {
        return;
      }

      StoreQueueItemStatus *wrapper = StoreQueueItemStatus::Unwrap<StoreQueueItemStatus>(info.This());

      try  {
        ::Windows::Services::Store::StoreQueueItemExtendedState result = wrapper->_instance->PackageInstallExtendedState;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PackageInstallStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info.This())) {
        return;
      }

      StoreQueueItemStatus *wrapper = StoreQueueItemStatus::Unwrap<StoreQueueItemStatus>(info.This());

      try  {
        ::Windows::Services::Store::StoreQueueItemState result = wrapper->_instance->PackageInstallState;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void UpdateStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemStatus^>(info.This())) {
        return;
      }

      StoreQueueItemStatus *wrapper = StoreQueueItemStatus::Unwrap<StoreQueueItemStatus>(info.This());

      try  {
        ::Windows::Services::Store::StorePackageUpdateStatus result = wrapper->_instance->UpdateStatus;
        info.GetReturnValue().Set(StorePackageUpdateStatusToJsObject(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreQueueItemStatus^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreQueueItemStatus(::Windows::Services::Store::StoreQueueItemStatus^ wintRtInstance);
      friend ::Windows::Services::Store::StoreQueueItemStatus^ UnwrapStoreQueueItemStatus(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreQueueItemStatus::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreQueueItemStatus(::Windows::Services::Store::StoreQueueItemStatus^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreQueueItemStatus::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreQueueItemStatus^ UnwrapStoreQueueItemStatus(Local<Value> value) {
     return StoreQueueItemStatus::Unwrap<StoreQueueItemStatus>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreQueueItemStatus(Local<Object> exports) {
    StoreQueueItemStatus::Init(exports);
  }

  class StoreQueueItemCompletedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreQueueItemCompletedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StoreQueueItemCompletedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreQueueItemCompletedEventArgs(::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemCompletedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreQueueItemCompletedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreQueueItemCompletedEventArgs *wrapperInstance = new StoreQueueItemCompletedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemCompletedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreQueueItemCompletedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreQueueItemCompletedEventArgs(winRtInstance));
    }





    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreQueueItemCompletedEventArgs^>(info.This())) {
        return;
      }

      StoreQueueItemCompletedEventArgs *wrapper = StoreQueueItemCompletedEventArgs::Unwrap<StoreQueueItemCompletedEventArgs>(info.This());

      try  {
        ::Windows::Services::Store::StoreQueueItemStatus^ result = wrapper->_instance->Status;
        info.GetReturnValue().Set(WrapStoreQueueItemStatus(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreQueueItemCompletedEventArgs(::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ wintRtInstance);
      friend ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ UnwrapStoreQueueItemCompletedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreQueueItemCompletedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreQueueItemCompletedEventArgs(::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreQueueItemCompletedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreQueueItemCompletedEventArgs^ UnwrapStoreQueueItemCompletedEventArgs(Local<Value> value) {
     return StoreQueueItemCompletedEventArgs::Unwrap<StoreQueueItemCompletedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreQueueItemCompletedEventArgs(Local<Object> exports) {
    StoreQueueItemCompletedEventArgs::Init(exports);
  }

  class StorePackageLicense : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorePackageLicense").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "releaseLicense", ReleaseLicense);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isValid").ToLocalChecked(), IsValidGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorePackageLicense").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorePackageLicense(::Windows::Services::Store::StorePackageLicense^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StorePackageLicense^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StorePackageLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorePackageLicense *wrapperInstance = new StorePackageLicense(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StorePackageLicense^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StorePackageLicense^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorePackageLicense(winRtInstance));
    }


    static void ReleaseLicense(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This())) {
        return;
      }

      StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->ReleaseLicense();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This())) {
        return;
      }

      StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void IsValidGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This())) {
        return;
      }

      StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());

      try  {
        bool result = wrapper->_instance->IsValid;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This())) {
        return;
      }

      StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());

      try  {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel", "Package", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"licenseLost", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->LicenseLost::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Services::Store::StorePackageLicense^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Services::Store::StorePackageLicense^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapStorePackageLicense(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"licenseLost", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"licenseLost", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StorePackageLicense^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          StorePackageLicense *wrapper = StorePackageLicense::Unwrap<StorePackageLicense>(info.This());
          wrapper->_instance->LicenseLost::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Services::Store::StorePackageLicense^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorePackageLicense(::Windows::Services::Store::StorePackageLicense^ wintRtInstance);
      friend ::Windows::Services::Store::StorePackageLicense^ UnwrapStorePackageLicense(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorePackageLicense::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorePackageLicense(::Windows::Services::Store::StorePackageLicense^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorePackageLicense::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StorePackageLicense^ UnwrapStorePackageLicense(Local<Value> value) {
     return StorePackageLicense::Unwrap<StorePackageLicense>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorePackageLicense(Local<Object> exports) {
    StorePackageLicense::Init(exports);
  }

  class StoreRequestHelper : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StoreRequestHelper").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(SendRequestAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("sendRequestAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("StoreRequestHelper").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StoreRequestHelper(::Windows::Services::Store::StoreRequestHelper^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Services::Store::StoreRequestHelper^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreRequestHelper^>(info[0])) {
        try {
          winRtInstance = (::Windows::Services::Store::StoreRequestHelper^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StoreRequestHelper *wrapperInstance = new StoreRequestHelper(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreRequestHelper^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Services::Store::StoreRequestHelper^ winRtInstance;
      try {
        winRtInstance = (::Windows::Services::Store::StoreRequestHelper^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStoreRequestHelper(winRtInstance));
    }




    static void SendRequestAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Services::Store::StoreSendRequestResult^>^ op;


      if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Services::Store::StoreContext^>(info[0])
          && info[1]->IsUint32()
          && info[2]->IsString())
      {
        try
        {
          ::Windows::Services::Store::StoreContext^ arg0 = UnwrapStoreContext(info[0]);
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
            
          op = ::Windows::Services::Store::StoreRequestHelper::SendRequestAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Services::Store::StoreSendRequestResult^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStoreSendRequestResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    private:
      ::Windows::Services::Store::StoreRequestHelper^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStoreRequestHelper(::Windows::Services::Store::StoreRequestHelper^ wintRtInstance);
      friend ::Windows::Services::Store::StoreRequestHelper^ UnwrapStoreRequestHelper(Local<Value> value);
  };

  Persistent<FunctionTemplate> StoreRequestHelper::s_constructorTemplate;

  v8::Local<v8::Value> WrapStoreRequestHelper(::Windows::Services::Store::StoreRequestHelper^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StoreRequestHelper::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Services::Store::StoreRequestHelper^ UnwrapStoreRequestHelper(Local<Value> value) {
     return StoreRequestHelper::Unwrap<StoreRequestHelper>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStoreRequestHelper(Local<Object> exports) {
    StoreRequestHelper::Init(exports);
  }


} } } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Services::Store::InitStorePurchaseStatusEnum(target);
      NodeRT::Windows::Services::Store::InitStoreConsumableStatusEnum(target);
      NodeRT::Windows::Services::Store::InitStoreDurationUnitEnum(target);
      NodeRT::Windows::Services::Store::InitStorePackageUpdateStateEnum(target);
      NodeRT::Windows::Services::Store::InitStoreCanLicenseStatusEnum(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItemStateEnum(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItemExtendedStateEnum(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItemKindEnum(target);
      NodeRT::Windows::Services::Store::InitStoreUninstallStorePackageStatusEnum(target);
      NodeRT::Windows::Services::Store::InitStoreProduct(target);
      NodeRT::Windows::Services::Store::InitStoreProductPagedQueryResult(target);
      NodeRT::Windows::Services::Store::InitStorePurchaseProperties(target);
      NodeRT::Windows::Services::Store::InitStoreLicense(target);
      NodeRT::Windows::Services::Store::InitStoreImage(target);
      NodeRT::Windows::Services::Store::InitStoreVideo(target);
      NodeRT::Windows::Services::Store::InitStoreSku(target);
      NodeRT::Windows::Services::Store::InitStorePrice(target);
      NodeRT::Windows::Services::Store::InitStorePurchaseResult(target);
      NodeRT::Windows::Services::Store::InitStoreAvailability(target);
      NodeRT::Windows::Services::Store::InitStoreCollectionData(target);
      NodeRT::Windows::Services::Store::InitStoreSubscriptionInfo(target);
      NodeRT::Windows::Services::Store::InitStoreContext(target);
      NodeRT::Windows::Services::Store::InitStoreSendRequestResult(target);
      NodeRT::Windows::Services::Store::InitStoreAppLicense(target);
      NodeRT::Windows::Services::Store::InitStoreProductResult(target);
      NodeRT::Windows::Services::Store::InitStoreProductQueryResult(target);
      NodeRT::Windows::Services::Store::InitStoreConsumableResult(target);
      NodeRT::Windows::Services::Store::InitStoreAcquireLicenseResult(target);
      NodeRT::Windows::Services::Store::InitStorePackageUpdate(target);
      NodeRT::Windows::Services::Store::InitStorePackageUpdateResult(target);
      NodeRT::Windows::Services::Store::InitStoreCanAcquireLicenseResult(target);
      NodeRT::Windows::Services::Store::InitStoreProductOptions(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItem(target);
      NodeRT::Windows::Services::Store::InitStorePackageInstallOptions(target);
      NodeRT::Windows::Services::Store::InitStoreUninstallStorePackageResult(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItemStatus(target);
      NodeRT::Windows::Services::Store::InitStoreQueueItemCompletedEventArgs(target);
      NodeRT::Windows::Services::Store::InitStorePackageLicense(target);
      NodeRT::Windows::Services::Store::InitStoreRequestHelper(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Services.Store", target);
}



NAN_MODULE_WORKER_ENABLED(binding, init)
