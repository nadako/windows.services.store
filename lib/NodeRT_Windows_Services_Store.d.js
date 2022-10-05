  
StoreContract = (function () {
  var cls = function StoreContract() {
    };
  return cls;
}) ();
exports.StoreContract = StoreContract;


  
StorePackageUpdateStatus = (function () {
  var cls = function StorePackageUpdateStatus() {
      this.packageFamilyName = new String();
      this.packageDownloadSizeInBytes = new Number();
      this.packageBytesDownloaded = new Number();
      this.packageDownloadProgress = new Number();
      this.totalDownloadProgress = new Number();
      this.packageUpdateState = new StorePackageUpdateState();
    };
  return cls;
}) ();
exports.StorePackageUpdateStatus = StorePackageUpdateStatus;


_StorePurchaseStatus = function () {
  this.succeeded = 0;
  this.alreadyPurchased = 1;
  this.notPurchased = 2;
  this.networkError = 3;
  this.serverError = 4;
}
exports.StorePurchaseStatus = new _StorePurchaseStatus();

_StoreConsumableStatus = function () {
  this.succeeded = 0;
  this.insufficentQuantity = 1;
  this.networkError = 2;
  this.serverError = 3;
}
exports.StoreConsumableStatus = new _StoreConsumableStatus();

_StoreDurationUnit = function () {
  this.minute = 0;
  this.hour = 1;
  this.day = 2;
  this.week = 3;
  this.month = 4;
  this.year = 5;
}
exports.StoreDurationUnit = new _StoreDurationUnit();

_StorePackageUpdateState = function () {
  this.pending = 0;
  this.downloading = 1;
  this.deploying = 2;
  this.completed = 3;
  this.canceled = 4;
  this.otherError = 5;
  this.errorLowBattery = 6;
  this.errorWiFiRecommended = 7;
  this.errorWiFiRequired = 8;
}
exports.StorePackageUpdateState = new _StorePackageUpdateState();

_StoreCanLicenseStatus = function () {
  this.notLicensableToUser = 0;
  this.licensable = 1;
  this.licenseActionNotApplicableToProduct = 2;
  this.networkError = 3;
  this.serverError = 4;
}
exports.StoreCanLicenseStatus = new _StoreCanLicenseStatus();

_StoreQueueItemState = function () {
  this.active = 0;
  this.completed = 1;
  this.canceled = 2;
  this.error = 3;
  this.paused = 4;
}
exports.StoreQueueItemState = new _StoreQueueItemState();

_StoreQueueItemExtendedState = function () {
  this.activePending = 0;
  this.activeStarting = 1;
  this.activeAcquiringLicense = 2;
  this.activeDownloading = 3;
  this.activeRestoringData = 4;
  this.activeInstalling = 5;
  this.completed = 6;
  this.canceled = 7;
  this.paused = 8;
  this.error = 9;
  this.pausedPackagesInUse = 10;
  this.pausedLowBattery = 11;
  this.pausedWiFiRecommended = 12;
  this.pausedWiFiRequired = 13;
  this.pausedReadyToInstall = 14;
}
exports.StoreQueueItemExtendedState = new _StoreQueueItemExtendedState();

_StoreQueueItemKind = function () {
  this.install = 0;
  this.update = 1;
  this.repair = 2;
}
exports.StoreQueueItemKind = new _StoreQueueItemKind();

_StoreUninstallStorePackageStatus = function () {
  this.succeeded = 0;
  this.canceledByUser = 1;
  this.networkError = 2;
  this.uninstallNotApplicable = 3;
  this.error = 4;
}
exports.StoreUninstallStorePackageStatus = new _StoreUninstallStorePackageStatus();

StoreProduct = (function () {
  var cls = function StoreProduct() {
    this.description = new String();
    this.extendedJsonData = new String();
    this.hasDigitalDownload = new Boolean();
    this.images = new Object();
    this.inAppOfferToken = new String();
    this.isInUserCollection = new Boolean();
    this.keywords = new Object();
    this.language = new String();
    this.linkUri = new Object();
    this.price = new StorePrice();
    this.productKind = new String();
    this.skus = new Object();
    this.storeId = new String();
    this.title = new String();
    this.videos = new Object();
  };
  

  cls.prototype.getIsAnySkuInstalledAsync = function getIsAnySkuInstalledAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(storePurchaseProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePurchaseProperties" type="StorePurchaseProperties">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.StoreProduct = StoreProduct;

StoreProductPagedQueryResult = (function () {
  var cls = function StoreProductPagedQueryResult() {
    this.extendedError = new Number();
    this.hasMoreResults = new Boolean();
    this.products = new Object();
  };
  

  cls.prototype.getNextAsync = function getNextAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.StoreProductPagedQueryResult = StoreProductPagedQueryResult;

StorePurchaseProperties = (function () {
  var cls = function StorePurchaseProperties() {
    this.name = new String();
    this.extendedJsonData = new String();
  };
  
var cls = function StorePurchaseProperties(name) {
      this.name = new String();
      this.extendedJsonData = new String();
};


  return cls;
}) ();
exports.StorePurchaseProperties = StorePurchaseProperties;

StoreLicense = (function () {
  var cls = function StoreLicense() {
    this.expirationDate = new Date();
    this.extendedJsonData = new String();
    this.inAppOfferToken = new String();
    this.isActive = new Boolean();
    this.skuStoreId = new String();
  };
  

  return cls;
}) ();
exports.StoreLicense = StoreLicense;

StoreImage = (function () {
  var cls = function StoreImage() {
    this.caption = new String();
    this.height = new Number();
    this.imagePurposeTag = new String();
    this.uri = new Object();
    this.width = new Number();
  };
  

  return cls;
}) ();
exports.StoreImage = StoreImage;

StoreVideo = (function () {
  var cls = function StoreVideo() {
    this.caption = new String();
    this.height = new Number();
    this.previewImage = new StoreImage();
    this.uri = new Object();
    this.videoPurposeTag = new String();
    this.width = new Number();
  };
  

  return cls;
}) ();
exports.StoreVideo = StoreVideo;

StoreSku = (function () {
  var cls = function StoreSku() {
    this.availabilities = new Object();
    this.bundledSkus = new Object();
    this.collectionData = new StoreCollectionData();
    this.customDeveloperData = new String();
    this.description = new String();
    this.extendedJsonData = new String();
    this.images = new Object();
    this.isInUserCollection = new Boolean();
    this.isSubscription = new Boolean();
    this.isTrial = new Boolean();
    this.language = new String();
    this.price = new StorePrice();
    this.storeId = new String();
    this.subscriptionInfo = new StoreSubscriptionInfo();
    this.title = new String();
    this.videos = new Object();
  };
  

  cls.prototype.getIsInstalledAsync = function getIsInstalledAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(storePurchaseProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePurchaseProperties" type="StorePurchaseProperties">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.StoreSku = StoreSku;

StorePrice = (function () {
  var cls = function StorePrice() {
    this.currencyCode = new String();
    this.formattedBasePrice = new String();
    this.formattedPrice = new String();
    this.formattedRecurrencePrice = new String();
    this.isOnSale = new Boolean();
    this.saleEndDate = new Date();
  };
  

  return cls;
}) ();
exports.StorePrice = StorePrice;

StorePurchaseResult = (function () {
  var cls = function StorePurchaseResult() {
    this.extendedError = new Number();
    this.status = new StorePurchaseStatus();
  };
  

  return cls;
}) ();
exports.StorePurchaseResult = StorePurchaseResult;

StoreAvailability = (function () {
  var cls = function StoreAvailability() {
    this.endDate = new Date();
    this.extendedJsonData = new String();
    this.price = new StorePrice();
    this.storeId = new String();
  };
  

  cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(storePurchaseProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePurchaseProperties" type="StorePurchaseProperties">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.StoreAvailability = StoreAvailability;

StoreCollectionData = (function () {
  var cls = function StoreCollectionData() {
    this.acquiredDate = new Date();
    this.campaignId = new String();
    this.developerOfferId = new String();
    this.endDate = new Date();
    this.extendedJsonData = new String();
    this.isTrial = new Boolean();
    this.startDate = new Date();
    this.trialTimeRemaining = new Number();
  };
  

  return cls;
}) ();
exports.StoreCollectionData = StoreCollectionData;

StoreSubscriptionInfo = (function () {
  var cls = function StoreSubscriptionInfo() {
    this.billingPeriod = new Number();
    this.billingPeriodUnit = new StoreDurationUnit();
    this.hasTrialPeriod = new Boolean();
    this.trialPeriod = new Number();
    this.trialPeriodUnit = new StoreDurationUnit();
  };
  

  return cls;
}) ();
exports.StoreSubscriptionInfo = StoreSubscriptionInfo;

StoreContext = (function () {
  var cls = function StoreContext() {
    this.user = new Object();
    this.canSilentlyDownloadStorePackageUpdates = new Boolean();
  };
  

  cls.prototype.getCustomerPurchaseIdAsync = function getCustomerPurchaseIdAsync(serviceTicket, publisherUserId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceTicket" type="String">A param.</param>
    /// <param name="publisherUserId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getCustomerCollectionsIdAsync = function getCustomerCollectionsIdAsync(serviceTicket, publisherUserId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceTicket" type="String">A param.</param>
    /// <param name="publisherUserId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getAppLicenseAsync = function getAppLicenseAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getStoreProductForCurrentAppAsync = function getStoreProductForCurrentAppAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getStoreProductsAsync = function getStoreProductsAsync(productKinds, storeIds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// <param name="storeIds" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.getStoreProductsAsync = function getStoreProductsAsync(productKinds, storeIds, storeProductOptions, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// <param name="storeIds" type="Object">A param.</param>
    /// <param name="storeProductOptions" type="StoreProductOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.getAssociatedStoreProductsAsync = function getAssociatedStoreProductsAsync(productKinds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getAssociatedStoreProductsWithPagingAsync = function getAssociatedStoreProductsWithPagingAsync(productKinds, maxItemsToRetrievePerPage, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// <param name="maxItemsToRetrievePerPage" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getUserCollectionAsync = function getUserCollectionAsync(productKinds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getUserCollectionWithPagingAsync = function getUserCollectionWithPagingAsync(productKinds, maxItemsToRetrievePerPage, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// <param name="maxItemsToRetrievePerPage" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.reportConsumableFulfillmentAsync = function reportConsumableFulfillmentAsync(productStoreId, quantity, trackingId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productStoreId" type="String">A param.</param>
    /// <param name="quantity" type="Number">A param.</param>
    /// <param name="trackingId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getConsumableBalanceRemainingAsync = function getConsumableBalanceRemainingAsync(productStoreId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productStoreId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.acquireStoreLicenseForOptionalPackageAsync = function acquireStoreLicenseForOptionalPackageAsync(optionalPackage, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="optionalPackage" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(storeId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeId" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.requestPurchaseAsync = function requestPurchaseAsync(storeId, storePurchaseProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeId" type="String">A param.</param>
    /// <param name="storePurchaseProperties" type="StorePurchaseProperties">A param.</param>
    /// </signature>
  }


  cls.prototype.getAppAndOptionalStorePackageUpdatesAsync = function getAppAndOptionalStorePackageUpdatesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.requestDownloadStorePackageUpdatesAsync = function requestDownloadStorePackageUpdatesAsync(storePackageUpdates, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePackageUpdates" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.requestDownloadAndInstallStorePackageUpdatesAsync = function requestDownloadAndInstallStorePackageUpdatesAsync(storePackageUpdates, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePackageUpdates" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.requestDownloadAndInstallStorePackagesAsync = function requestDownloadAndInstallStorePackagesAsync(storeIds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeIds" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.requestDownloadAndInstallStorePackagesAsync = function requestDownloadAndInstallStorePackagesAsync(storeIds, storePackageInstallOptions, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeIds" type="Object">A param.</param>
    /// <param name="storePackageInstallOptions" type="StorePackageInstallOptions">A param.</param>
    /// </signature>
  }


  cls.prototype.findStoreProductForPackageAsync = function findStoreProductForPackageAsync(productKinds, package, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productKinds" type="Object">A param.</param>
    /// <param name="package" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.trySilentDownloadStorePackageUpdatesAsync = function trySilentDownloadStorePackageUpdatesAsync(storePackageUpdates, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePackageUpdates" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.trySilentDownloadAndInstallStorePackageUpdatesAsync = function trySilentDownloadAndInstallStorePackageUpdatesAsync(storePackageUpdates, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storePackageUpdates" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.canAcquireStoreLicenseForOptionalPackageAsync = function canAcquireStoreLicenseForOptionalPackageAsync(optionalPackage, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="optionalPackage" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.canAcquireStoreLicenseAsync = function canAcquireStoreLicenseAsync(productStoreId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="productStoreId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getAssociatedStoreQueueItemsAsync = function getAssociatedStoreQueueItemsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getStoreQueueItemsAsync = function getStoreQueueItemsAsync(storeIds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeIds" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.downloadAndInstallStorePackagesAsync = function downloadAndInstallStorePackagesAsync(storeIds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeIds" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.requestUninstallStorePackageAsync = function requestUninstallStorePackageAsync(package, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="package" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.requestUninstallStorePackageByStoreIdAsync = function requestUninstallStorePackageByStoreIdAsync(storeId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.uninstallStorePackageAsync = function uninstallStorePackageAsync(package, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="package" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.uninstallStorePackageByStoreIdAsync = function uninstallStorePackageByStoreIdAsync(storeId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="storeId" type="String">A param.</param>
    /// </signature>
  }


  cls.getDefault = function getDefault() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="StoreContext" />
    /// </signature>
    return new StoreContext();
  }


  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="StoreContext" />
    /// </signature>
    return new StoreContext();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.StoreContext = StoreContext;

StoreSendRequestResult = (function () {
  var cls = function StoreSendRequestResult() {
    this.extendedError = new Number();
    this.response = new String();
    this.httpStatusCode = new Number();
  };
  

  return cls;
}) ();
exports.StoreSendRequestResult = StoreSendRequestResult;

StoreAppLicense = (function () {
  var cls = function StoreAppLicense() {
    this.addOnLicenses = new Object();
    this.expirationDate = new Date();
    this.extendedJsonData = new String();
    this.isActive = new Boolean();
    this.isTrial = new Boolean();
    this.isTrialOwnedByThisUser = new Boolean();
    this.skuStoreId = new String();
    this.trialTimeRemaining = new Number();
    this.trialUniqueId = new String();
  };
  

  return cls;
}) ();
exports.StoreAppLicense = StoreAppLicense;

StoreProductResult = (function () {
  var cls = function StoreProductResult() {
    this.extendedError = new Number();
    this.product = new StoreProduct();
  };
  

  return cls;
}) ();
exports.StoreProductResult = StoreProductResult;

StoreProductQueryResult = (function () {
  var cls = function StoreProductQueryResult() {
    this.extendedError = new Number();
    this.products = new Object();
  };
  

  return cls;
}) ();
exports.StoreProductQueryResult = StoreProductQueryResult;

StoreConsumableResult = (function () {
  var cls = function StoreConsumableResult() {
    this.balanceRemaining = new Number();
    this.extendedError = new Number();
    this.status = new StoreConsumableStatus();
    this.trackingId = new String();
  };
  

  return cls;
}) ();
exports.StoreConsumableResult = StoreConsumableResult;

StoreAcquireLicenseResult = (function () {
  var cls = function StoreAcquireLicenseResult() {
    this.extendedError = new Number();
    this.storePackageLicense = new StorePackageLicense();
  };
  

  return cls;
}) ();
exports.StoreAcquireLicenseResult = StoreAcquireLicenseResult;

StorePackageUpdate = (function () {
  var cls = function StorePackageUpdate() {
    this.mandatory = new Boolean();
    this.package = new Object();
  };
  

  return cls;
}) ();
exports.StorePackageUpdate = StorePackageUpdate;

StorePackageUpdateResult = (function () {
  var cls = function StorePackageUpdateResult() {
    this.overallState = new StorePackageUpdateState();
    this.storePackageUpdateStatuses = new Object();
    this.storeQueueItems = new Object();
  };
  

  return cls;
}) ();
exports.StorePackageUpdateResult = StorePackageUpdateResult;

StoreCanAcquireLicenseResult = (function () {
  var cls = function StoreCanAcquireLicenseResult() {
    this.extendedError = new Number();
    this.licensableSku = new String();
    this.status = new StoreCanLicenseStatus();
  };
  

  return cls;
}) ();
exports.StoreCanAcquireLicenseResult = StoreCanAcquireLicenseResult;

StoreProductOptions = (function () {
  var cls = function StoreProductOptions() {
    this.actionFilters = new Object();
  };
  

  return cls;
}) ();
exports.StoreProductOptions = StoreProductOptions;

StoreQueueItem = (function () {
  var cls = function StoreQueueItem() {
    this.installKind = new StoreQueueItemKind();
    this.packageFamilyName = new String();
    this.productId = new String();
  };
  

  cls.prototype.getCurrentStatus = function getCurrentStatus() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="StoreQueueItemStatus" />
    /// </signature>
    return new StoreQueueItemStatus();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.StoreQueueItem = StoreQueueItem;

StorePackageInstallOptions = (function () {
  var cls = function StorePackageInstallOptions() {
    this.allowForcedAppRestart = new Boolean();
  };
  

  return cls;
}) ();
exports.StorePackageInstallOptions = StorePackageInstallOptions;

StoreUninstallStorePackageResult = (function () {
  var cls = function StoreUninstallStorePackageResult() {
    this.extendedError = new Number();
    this.status = new StoreUninstallStorePackageStatus();
  };
  

  return cls;
}) ();
exports.StoreUninstallStorePackageResult = StoreUninstallStorePackageResult;

StoreQueueItemStatus = (function () {
  var cls = function StoreQueueItemStatus() {
    this.extendedError = new Number();
    this.packageInstallExtendedState = new StoreQueueItemExtendedState();
    this.packageInstallState = new StoreQueueItemState();
    this.updateStatus = new StorePackageUpdateStatus();
  };
  

  return cls;
}) ();
exports.StoreQueueItemStatus = StoreQueueItemStatus;

StoreQueueItemCompletedEventArgs = (function () {
  var cls = function StoreQueueItemCompletedEventArgs() {
    this.status = new StoreQueueItemStatus();
  };
  

  return cls;
}) ();
exports.StoreQueueItemCompletedEventArgs = StoreQueueItemCompletedEventArgs;

StorePackageLicense = (function () {
  var cls = function StorePackageLicense() {
    this.isValid = new Boolean();
    this.package = new Object();
  };
  

  cls.prototype.releaseLicense = function releaseLicense() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.StorePackageLicense = StorePackageLicense;

StoreRequestHelper = (function () {
  var cls = function StoreRequestHelper() {
  };
  

  cls.sendRequestAsync = function sendRequestAsync(context, requestKind, parametersAsJson, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="context" type="StoreContext">A param.</param>
    /// <param name="requestKind" type="Number">A param.</param>
    /// <param name="parametersAsJson" type="String">A param.</param>
    /// </signature>
  }



  return cls;
}) ();
exports.StoreRequestHelper = StoreRequestHelper;

